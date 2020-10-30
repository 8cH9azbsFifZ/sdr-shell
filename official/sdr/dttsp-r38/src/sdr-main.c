/* sdr-main.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2004, 2005, 2006 by Frank Brickle, AB2KT and Bob McGwier, N4HY

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The authors can be reached by email at

ab2kt@arrl.net
or
rwmcgwier@comcast.net

or by paper mail at

The DTTS Microwave Society
6 Kathleen Place
Bridgewater, NJ 08807
*/

///////////////////////////////////////////////////////////////////////

#include <common.h>

// elementary defaults

struct _loc loc;

/////////////////////////////////////////////////////////////////////////
// most of what little we know here about the inner loop,
// functionally speaking

extern void reset_meters(void);
extern void reset_spectrum(void);
extern void reset_counters(void);
extern void process_samples(float *, float *, float *, float *, int);
extern void setup_workspace(REAL rate,
			    int buflen,
			    SDRMODE mode,
			    char *wisdom,
			    int specsize,
			    int numrecv,
			    int cpdsize);
extern void destroy_workspace(void);
extern int reset_for_buflen(int new_buflen);

// reset_for_samplerate() deprecated since can't be done under jack

//========================================================================

PRIVATE void
spectrum_thread(void) {
  while (top->running) {
    sem_wait(&top->sync.pws.sem);
    sem_wait(&top->sync.upd.sem);

    if (fwrite((char *) &uni->spec.label, sizeof(int), 1, top->meas.spec.fp)
	!= 1) {
      fprintf(stderr, "error writing spectrum label\n");
      exit(1);
    }

    // spec points or waveform?
    if (uni->spec.last == SPEC_LAST_FREQ) {
      compute_spectrum(&uni->spec);
      if (fwrite((char *) uni->spec.output, sizeof(float), uni->spec.size, top->meas.spec.fp)
	  != uni->spec.size) {
	fprintf(stderr, "error writing spectrum\n");
	exit(1);
      }

    } else {
      if (fwrite((char *) uni->spec.oscope, sizeof(float), uni->spec.size, top->meas.spec.fp)
	  != uni->spec.size) {
	fprintf(stderr, "error writing oscope\n");
	exit(1);
      }
    }

    fflush(top->meas.spec.fp);
    sem_post(&top->sync.upd.sem);
  }

  pthread_exit(0);
}

PRIVATE void
meter_thread(void) {
  while (top->running) {
    sem_wait(&top->sync.mtr.sem);
    sem_wait(&top->sync.upd.sem);

    if (fwrite((char *) &uni->meter.label, sizeof(int), 1, top->meas.mtr.fp)
	!= 1) {
      fprintf(stderr, "error writing meter label\n");
      exit(1);
    }

    // RX or TX?
    if (uni->meter.last == METER_LAST_RX) {
      if (fwrite((char *) uni->meter.snap.rx,
		 sizeof(REAL),
		 MAXRX * RXMETERPTS,
		 top->meas.mtr.fp)
	  != MAXRX * RXMETERPTS) {
	fprintf(stderr, "error writing rx meter\n");
	exit(1);
      }
    } else {
      if (fwrite((char *) uni->meter.snap.tx,
		 sizeof(REAL),
		 TXMETERPTS,
		 top->meas.mtr.fp)
	  != TXMETERPTS) {
	fprintf(stderr, "error writing tx meter\n");
	exit(1);
      }
    }

    fflush(top->meas.mtr.fp);
    sem_post(&top->sync.upd.sem);
  }

  pthread_exit(0);
}

//========================================================================

PRIVATE void
monitor_thread(void) {
  while (top->running) {
    sem_wait(&top->sync.mon.sem);
    
    // If there is anything that needs monitoring, do it here
    fprintf(top->jack.blow.fp,
	    "@@@ mon [%s %d]: rbi = %d rbo = %d xr = %d\n",
	    top->jack.name,
	    uni->tick,
	    top->jack.blow.rb.i,
	    top->jack.blow.rb.o,
	    top->jack.blow.xr);
    fflush(top->jack.blow.fp);
    top->jack.blow.rb.i = top->jack.blow.rb.o = top->jack.blow.xr = 0;
  }

  pthread_exit(0);
}

//========================================================================

PRIVATE void
process_updates_thread(void) {
  while (top->running) {
    pthread_testcancel();

    while (fgets(top->parm.buff, sizeof(top->parm.buff), top->parm.fp))
      do_update(top->parm.buff, top->verbose ? top->echo.fp : 0);
  }

  pthread_exit(0);
}

//========================================================================

PRIVATE void
gethold(void) {
  if ((ringb_float_write_space(top->jack.ring.o.l) < top->hold.size.frames) ||
      (ringb_float_write_space(top->jack.ring.o.r) < top->hold.size.frames) ||
      (ringb_float_write_space(top->jack.auxr.o.l) < top->hold.size.frames) ||
      (ringb_float_write_space(top->jack.auxr.o.r) < top->hold.size.frames)) {
    // pathology
    top->jack.blow.rb.o++;
  } else {
    ringb_float_write(top->jack.ring.o.l,
		      top->hold.buf.l,
		      top->hold.size.frames);
    ringb_float_write(top->jack.ring.o.r,
		      top->hold.buf.r,
		      top->hold.size.frames);
    ringb_float_write(top->jack.auxr.o.l,
		      top->hold.aux.l,
		      top->hold.size.frames);
    ringb_float_write(top->jack.auxr.o.r,
		      top->hold.aux.r,
		      top->hold.size.frames);
  }

  if ((ringb_float_read_space(top->jack.ring.i.l) < top->hold.size.frames) ||
      (ringb_float_read_space(top->jack.ring.i.r) < top->hold.size.frames) ||
      (ringb_float_read_space(top->jack.auxr.i.l) < top->hold.size.frames) ||
      (ringb_float_read_space(top->jack.auxr.i.l) < top->hold.size.frames)) {
    // pathology
    memset((char *) top->hold.buf.l, 0, top->hold.size.bytes);
    memset((char *) top->hold.buf.r, 0, top->hold.size.bytes);
    memset((char *) top->hold.aux.l, 0, top->hold.size.bytes);
    memset((char *) top->hold.aux.r, 0, top->hold.size.bytes);
    top->jack.blow.rb.i++;
  } else {
    ringb_float_read(top->jack.ring.i.l, top->hold.buf.l, top->hold.size.frames);
    ringb_float_read(top->jack.ring.i.r, top->hold.buf.r, top->hold.size.frames);
    ringb_float_read(top->jack.auxr.i.l, top->hold.aux.l, top->hold.size.frames);
    ringb_float_read(top->jack.auxr.i.r, top->hold.aux.r, top->hold.size.frames);
  }
}

PRIVATE BOOLEAN
canhold(void) {
  return
    (ringb_float_read_space(top->jack.ring.i.l) >= top->hold.size.frames) &&
    (ringb_float_read_space(top->jack.ring.i.r) >= top->hold.size.frames) &&
    (ringb_float_read_space(top->jack.auxr.i.l) >= top->hold.size.frames) &&
    (ringb_float_read_space(top->jack.auxr.i.l) >= top->hold.size.frames);
}

//------------------------------------------------------------------------

PRIVATE void
run_mute(void) {
  memset((char *) top->hold.buf.l, 0, top->hold.size.bytes);
  memset((char *) top->hold.buf.r, 0, top->hold.size.bytes);
  memset((char *) top->hold.aux.l, 0, top->hold.size.bytes);
  memset((char *) top->hold.aux.r, 0, top->hold.size.bytes);
  uni->tick++;
}

PRIVATE void
run_pass(void) { uni->tick++; }

PRIVATE void
run_play(void) {
  process_samples(top->hold.buf.l, top->hold.buf.r,
		  top->hold.aux.l, top->hold.aux.r,
		  top->hold.size.frames);
}

// NB do not set RUN_SWCH directly via setRunState;
// use setSWCH instead

PRIVATE void
run_swch(void) {
  int i, n = top->hold.size.frames;
  REAL w;

  for (i = 0; i < n; i++) {

    if (top->swch.env.curr.type == SWCH_FALL) {
      top->swch.env.curr.val += top->swch.env.fall.incr;
      w = sin(top->swch.env.curr.val * M_PI /  2.0);
      top->hold.buf.l[i] *= w, top->hold.buf.r[i] *= w;
      top->hold.aux.l[i] *= w, top->hold.aux.r[i] *= w;

      if (++top->swch.env.curr.cnt >= top->swch.env.fall.size) {
	top->swch.env.curr.type = SWCH_STDY;
	top->swch.env.curr.cnt = 0;
	top->swch.env.curr.val = 0.0;
      }

    } else if (top->swch.env.curr.type == SWCH_STDY) {
      top->hold.buf.l[i]= top->hold.buf.r[i] =
	top->hold.aux.l[i] =  top->hold.aux.r[i] = 0.0;

      if (++top->swch.env.curr.cnt >= top->swch.env.stdy.size) {
	top->swch.env.curr.type = SWCH_RISE;
	top->swch.env.curr.cnt = 0;
	top->swch.env.curr.val = 0.0;
      }

    } else if (top->swch.env.curr.type == SWCH_RISE) {
      top->swch.env.curr.val += top->swch.env.rise.incr;
      w = sin(top->swch.env.curr.val * M_PI /  2.0);
      top->hold.buf.l[i] *= w, top->hold.buf.r[i] *= w;
      top->hold.aux.l[i] *= w, top->hold.aux.r[i] *= w;

      if (++top->swch.env.curr.cnt >= top->swch.env.rise.size) {
	reset_meters();
	reset_spectrum();
	reset_counters();
	
	uni->mode.trx = top->swch.trx.next;
	top->state = top->swch.run.last;
      }
    }
  }

  process_samples(top->hold.buf.l, top->hold.buf.r,
		  top->hold.aux.l, top->hold.aux.r,
		  top->hold.size.frames);
}

//========================================================================

PRIVATE void 
audio_callback(jack_nframes_t nframes, void *arg) {
  float *lp, *rp;
  int nbytes = nframes * sizeof(float);

  if (top->jack.doin) {
    int i;
    const float zero = 0.0;
    size_t rsiz = max(top->jack.rsiz, nframes);
    
    ringb_float_reset(top->jack.ring.i.l);
    ringb_float_reset(top->jack.ring.i.r);
    ringb_float_reset(top->jack.auxr.i.l);
    ringb_float_reset(top->jack.auxr.i.r);
    
    for (i = top->offs; i < 0; i++) {
      ringb_float_write(top->jack.ring.i.l, &zero, 1);
      ringb_float_write(top->jack.auxr.i.l, &zero, 1);
    }
    for (i = 0; i < top->offs; i++) {
      ringb_float_write(top->jack.ring.i.r, &zero, 1);
      ringb_float_write(top->jack.auxr.i.r, &zero, 1);
    }
    
    ringb_float_restart(top->jack.ring.o.r, rsiz);
    ringb_float_restart(top->jack.ring.o.l, rsiz);
    ringb_float_restart(top->jack.auxr.o.r, rsiz);
    ringb_float_restart(top->jack.auxr.o.l, rsiz);
    
    top->jack.doin = FALSE;
  }

  if (top->susp) {
    lp = (float *) jack_port_get_buffer(top->jack.port.o.l, nframes);
    rp = (float *) jack_port_get_buffer(top->jack.port.o.r, nframes);
    memset((char *) lp, 0, nbytes);
    memset((char *) rp, 0, nbytes);
    lp = (float *) jack_port_get_buffer(top->jack.auxp.o.l, nframes);
    rp = (float *) jack_port_get_buffer(top->jack.auxp.o.r, nframes);
    memset((char *) lp, 0, nbytes);
    memset((char *) rp, 0, nbytes);
    return;
  }
  
  // output: copy from ring to port
  
  lp = (float *) jack_port_get_buffer(top->jack.port.o.l, nframes);
  rp = (float *) jack_port_get_buffer(top->jack.port.o.r, nframes);
  
  if (ringb_float_read_space(top->jack.ring.o.l) >= nframes) {
    ringb_float_read(top->jack.ring.o.l, lp, nframes);
    ringb_float_read(top->jack.ring.o.r, rp, nframes);
  } else {
    memset((char *) lp, 0, nbytes);
    memset((char *) rp, 0, nbytes);
    ringb_float_reset(top->jack.ring.o.l);
    ringb_float_reset(top->jack.ring.o.r);
    ringb_float_clear(top->jack.ring.o.l, nframes);
    ringb_float_clear(top->jack.ring.o.r, nframes);
    top->jack.blow.rb.o++;
  }
  
  lp = (float *) jack_port_get_buffer(top->jack.auxp.o.l, nframes);
  rp = (float *) jack_port_get_buffer(top->jack.auxp.o.r, nframes);
  
  if (ringb_float_read_space(top->jack.auxr.o.l) >= nframes) {
    ringb_float_read(top->jack.auxr.o.l, lp, nframes);
    ringb_float_read(top->jack.auxr.o.r, rp, nframes);
  } else {
    memset((char *) lp, 0, nbytes);
    memset((char *) rp, 0, nbytes);
    ringb_float_reset(top->jack.auxr.o.l);
    ringb_float_reset(top->jack.auxr.o.r);
    ringb_float_clear(top->jack.auxr.o.l, nframes);
    ringb_float_clear(top->jack.auxr.o.r, nframes);
    top->jack.blow.rb.o++;
  }
  
  // input: copy from port to ring
  if (ringb_float_write_space(top->jack.ring.i.l) >= nframes) {
    lp = (float *) jack_port_get_buffer(top->jack.port.i.l, nframes);
    rp = (float *) jack_port_get_buffer(top->jack.port.i.r, nframes);
    ringb_float_write(top->jack.ring.i.l, lp, nframes);
    ringb_float_write(top->jack.ring.i.r, rp, nframes);
    lp = (float *) jack_port_get_buffer(top->jack.auxp.i.l, nframes);
    rp = (float *) jack_port_get_buffer(top->jack.auxp.i.r, nframes);
    ringb_float_write(top->jack.auxr.i.l, lp, nframes);
    ringb_float_write(top->jack.auxr.i.r, rp, nframes);
  } else {
    top->jack.doin = TRUE;
    top->jack.blow.rb.i++;
  }
  
  // if enough accumulated in ring, fire dsp
  if ((ringb_float_read_space(top->jack.ring.i.l) >= top->hold.size.frames) &&
      (ringb_float_read_space(top->jack.ring.i.r) >= top->hold.size.frames) &&
      (ringb_float_read_space(top->jack.auxr.i.l) >= top->hold.size.frames) &&
      (ringb_float_read_space(top->jack.auxr.i.r) >= top->hold.size.frames))
    sem_post(&top->sync.buf.sem);
  
  // check for blowups
  if ((top->jack.blow.rb.i > 0) || (top->jack.blow.rb.o > 0))
    sem_post(&top->sync.mon.sem);
}

//========================================================================

PRIVATE void
process_samples_thread(void) {
  while (top->running) {
    sem_wait(&top->sync.buf.sem);
    do {
      gethold();
      sem_wait(&top->sync.upd.sem);
      switch (top->state) {
      case RUN_MUTE: run_mute(); break;
      case RUN_PASS: run_pass(); break;
      case RUN_PLAY: run_play(); break;
      case RUN_SWCH: run_swch(); break;
      }
      sem_post(&top->sync.upd.sem);
    } while (canhold());
  }
}

//========================================================================

PRIVATE void
execute(void) {
  // let updates run
  sem_post(&top->sync.upd.sem);
  
  // rcfile
  {
    FILE *frc = find_rcfile(loc.path.rcfile);
    if (frc) {
      while (fgets(top->parm.buff, sizeof(top->parm.buff), frc))
	do_update(top->parm.buff, top->echo.fp ? stderr : 0);
      fclose(frc);
    }
  }

  // start audio processing
  if (jack_activate(top->jack.client))
    fprintf(stderr, "cannot activate jack client"), exit(1);

  // final shutdown always starts in update thread,
  // so join it first
  pthread_join(top->thrd.upd.id, 0);

  // issue cancellation notices
  pthread_cancel(top->thrd.trx.id);
  pthread_cancel(top->thrd.mon.id);
  if (uni->meter.flag)
    pthread_cancel(top->thrd.mtr.id);
  if (uni->spec.flag)
    pthread_cancel(top->thrd.pws.id);

  // wait for remaining threads to finish
  pthread_join(top->thrd.trx.id, 0);
  pthread_join(top->thrd.mon.id, 0);
  if (uni->meter.flag)
    pthread_join(top->thrd.mtr.id, 0);
  if (uni->spec.flag)
    pthread_join(top->thrd.pws.id, 0);
  
  // stop audio processing
  jack_client_close(top->jack.client);
}

//........................................................................


PRIVATE void
setup_local_audio(void) {
  top->offs = loc.skew.offs;
  top->hold.size.frames = uni->buflen;
  top->hold.size.bytes = top->hold.size.frames * sizeof(float);
  top->hold.buf.l = (float *) safealloc(top->hold.size.frames,
				       sizeof(float),
				       "main hold buffer left");
  top->hold.buf.r = (float *) safealloc(top->hold.size.frames,
				       sizeof(float),
				       "main hold buffer right");
  top->hold.aux.l = (float *) safealloc(top->hold.size.frames,
				       sizeof(float),
				       "aux hold buffer left");
  top->hold.aux.r = (float *) safealloc(top->hold.size.frames,
				       sizeof(float),
				       "aux hold buffer right");
}

PRIVATE void 
setup_updates(void) {
  top->parm.path = loc.path.parm;
  if ((top->parm.fd = open(top->parm.path, O_RDWR)) == -1)
    perror(top->parm.path), exit(1);
  if (!(top->parm.fp = fdopen(top->parm.fd, "r+"))) {
    fprintf(stderr, "can't fdopen parm pipe %s\n", loc.path.parm);
    exit(1);
  }

  // do this here 'cuz the update thread is controlling the action
  if (uni->meter.flag) {
    top->meas.mtr.path = loc.path.meter;
    top->meas.mtr.fp = efopen(top->meas.mtr.path, "r+");
  }
  if (uni->spec.flag) {
    top->meas.spec.path = loc.path.spec;
    top->meas.spec.fp = efopen(top->meas.spec.path, "r+");
  }

  if (uni->update.path = loc.path.replay) {
    uni->update.flag = TRUE;
    uni->update.fp = efopen(uni->update.path, "w+");
  }

  if (top->verbose) {
    if (loc.path.echo[0]) {
      top->echo.path = loc.path.echo;
      if ((top->echo.fd = open(top->echo.path, O_RDWR)) == -1)
	perror(top->echo.path), exit(1);
      if (!(top->echo.fp = fdopen(top->echo.fd, "r+"))) {
	fprintf(stderr, "can't fdopen echo file %s\n", loc.path.echo);
	exit(1);
      }
    } else {
      top->echo.path = 0;
      top->echo.fp = stderr;
      top->echo.fd = fileno(top->echo.fp);
    }
  }

  if (loc.path.blowr[0]) {
    top->jack.blow.path = loc.path.blowr;
    if ((top->jack.blow.fd = open(top->jack.blow.path, O_RDWR)) == -1)
      perror(top->jack.blow.path), exit(1);
    if (!(top->jack.blow.fp = fdopen(top->jack.blow.fd, "r+"))) {
      fprintf(stderr, "can't fdopen blowr file %s\n", loc.path.blowr);
      exit(1);
    }
  } else {
    top->jack.blow.path = 0;
    top->jack.blow.fp = stderr;
    top->jack.blow.fd = fileno(top->jack.blow.fp);
  }
}

PRIVATE void
jack_xrun(void *arg) {
  top->jack.blow.xr++;
  sem_post(&top->sync.mon.sem);
}

PRIVATE void
jack_shutdown(void *arg) {}

PRIVATE void
setup_system_audio(void) {
  top->jack.blow.rb.i = top->jack.blow.rb.o = top->jack.blow.xr = 0;
    
  if (loc.name[0])
    strcpy(top->jack.name, loc.name);
  else
    sprintf(top->jack.name, "sdr-%d", top->pid);
  if (!(top->jack.client = jack_client_new(top->jack.name)))
    perror("can't make client -- jack not running?"), exit(1);

  jack_set_process_callback(top->jack.client, (void *) audio_callback, 0);
  jack_on_shutdown(top->jack.client, (void *) jack_shutdown, 0);
  jack_set_xrun_callback(top->jack.client, (void *) jack_xrun, 0);
  top->jack.size = jack_get_buffer_size(top->jack.client);

  top->jack.port.i.l = jack_port_register(top->jack.client,
                                          "il",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsInput,
					  0);
  top->jack.port.i.r = jack_port_register(top->jack.client,
					  "ir",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsInput,
					  0);
  top->jack.port.o.l = jack_port_register(top->jack.client,
					  "ol",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput,
					  0);
  top->jack.port.o.r = jack_port_register(top->jack.client,
					  "or",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput,
					  0);
  top->jack.auxp.i.l = jack_port_register(top->jack.client,
					  "al",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsInput,
					  0);
  top->jack.auxp.i.r = jack_port_register(top->jack.client,
					  "ar",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsInput,
					  0);
  top->jack.auxp.o.l = jack_port_register(top->jack.client,
					  "tl",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput,
					  0);
  top->jack.auxp.o.r = jack_port_register(top->jack.client,
					  "tr",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput,
					  0);

  top->jack.ring.i.l = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.ring.i.r = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.ring.o.l = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.ring.o.r = ringb_float_create(top->jack.size * loc.mult.ring);

  top->jack.auxr.i.l = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.auxr.i.r = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.auxr.o.l = ringb_float_create(top->jack.size * loc.mult.ring);
  top->jack.auxr.o.r = ringb_float_create(top->jack.size * loc.mult.ring);

  top->jack.doin = TRUE;
}

PRIVATE void
setup_threading(void) {
  sem_init(&top->sync.upd.sem, 0, 0);
  pthread_create(&top->thrd.upd.id, 0, (void *) process_updates_thread, 0);
  sem_init(&top->sync.buf.sem, 0, 0);
  pthread_create(&top->thrd.trx.id, 0, (void *) process_samples_thread, 0);
  sem_init(&top->sync.mon.sem, 0, 0);
  pthread_create(&top->thrd.mon.id, 0, (void *) monitor_thread, 0);

  top->susp = FALSE;

  if (uni->meter.flag) {
    sem_init(&top->sync.mtr.sem, 0, 0);
    pthread_create(&top->thrd.mtr.id, 0, (void *) meter_thread, 0);
  }
  if (uni->spec.flag) {
    sem_init(&top->sync.pws.sem, 0, 0);
    pthread_create(&top->thrd.pws.id, 0, (void *) spectrum_thread, 0);
  }
}

//========================================================================
// hard defaults, then environment

PRIVATE void
setup_defaults(void) {
  // no env vars for these
  loc.name[0] = 0; // no default for client name, period
  loc.path.blowr[0] = 0; // file defaults to stderr
  loc.path.echo[0] = 0;  // file defaults to stderr

  strcpy(loc.path.meter,  METERPATH);
  strcpy(loc.path.parm,   PARMPATH);
  strcpy(loc.path.rcfile, RCBASE);
  strcpy(loc.path.replay, REPLAYPATH);
  strcpy(loc.path.spec,   SPECPATH);
  strcpy(loc.path.wisdom, WISDOMPATH);

  loc.def.comp =  DEFCOMP;
  loc.def.mode =  DEFMODE;
  loc.def.nrx =   MAXRX;
  loc.def.rate =  DEFRATE;
  loc.def.size =  DEFSIZE;
  loc.def.spec =  DEFSPEC;
  loc.mult.ring = RINGMULT;
  loc.skew.offs = DEFOFFS;

  {
    char *ep;
    if ((ep = getenv("SDR_DEFMODE")))    loc.def.mode = atoi(ep);
    if ((ep = getenv("SDR_DEFRATE")))    loc.def.rate = atof(ep);
    if ((ep = getenv("SDR_DEFSIZE")))    loc.def.size = atoi(ep);
    if ((ep = getenv("SDR_RINGMULT")))   loc.mult.ring = atoi(ep);
    if ((ep = getenv("SDR_SKEWOFFS")))   loc.skew.offs = atoi(ep);
    if ((ep = getenv("SDR_BLOWRPATH")))  strcpy(loc.path.blowr, ep);
    if ((ep = getenv("SDR_METERPATH")))  strcpy(loc.path.meter, ep);
    if ((ep = getenv("SDR_NAME")))       strcpy(loc.name, ep);
    if ((ep = getenv("SDR_PARMPATH")))   strcpy(loc.path.parm, ep);
    if ((ep = getenv("SDR_RCBASE")))     strcpy(loc.path.rcfile, ep);
    if ((ep = getenv("SDR_REPLAYPATH"))) strcpy(loc.path.replay, ep);
    if ((ep = getenv("SDR_SPECPATH")))   strcpy(loc.path.spec, ep);
    if ((ep = getenv("SDR_WISDOMPATH"))) strcpy(loc.path.wisdom, ep);
  }
}

//========================================================================

int
reset_for_buflen(int new_buflen) {

  // make sure new size is power of 2
  if (popcnt(new_buflen) != 1)
    return -1;

  safefree((char *) top->hold.buf.r);
  safefree((char *) top->hold.buf.l);
  safefree((char *) top->hold.aux.r);
  safefree((char *) top->hold.aux.l);

  destroy_workspace();

  fprintf(stderr, "safemem %d\n", safememcurrcount());
  safememreset();

  loc.def.size = new_buflen;
  setup_workspace(loc.def.rate,
		  loc.def.size = new_buflen,
		  loc.def.mode,
		  loc.path.wisdom, 
		  loc.def.spec, 
		  loc.def.nrx, 
		  loc.def.size);

  setup_local_audio();

  reset_meters();
  reset_spectrum();
  reset_counters();

  return 0;
}

PRIVATE void
destroy_globals(void) {
  int i;
  safefree((char *) tx);
  for (i = 0; i < MAXRX; i++)
    safefree((char *) rx[i]);
  safefree((char *) uni);
  safefree((char *) top);
}

PRIVATE void 
closeup(void) {
  ringb_float_free(top->jack.auxr.o.r);
  ringb_float_free(top->jack.auxr.o.l);
  ringb_float_free(top->jack.auxr.i.r);
  ringb_float_free(top->jack.auxr.i.l);
  ringb_float_free(top->jack.ring.o.r);
  ringb_float_free(top->jack.ring.o.l);
  ringb_float_free(top->jack.ring.i.r);
  ringb_float_free(top->jack.ring.i.l);

  safefree((char *) top->hold.buf.r);
  safefree((char *) top->hold.buf.l);
  safefree((char *) top->hold.aux.r);
  safefree((char *) top->hold.aux.l);

  fclose(top->parm.fp);
  if (top->jack.blow.fp != stderr)
    fclose(top->jack.blow.fp);
  if (top->verbose && top->echo.fp != stderr)
    fclose(top->echo.fp);

  if (uni->meter.flag)
    fclose(top->meas.mtr.fp);
  if (uni->spec.flag)
    fclose(top->meas.spec.fp);
  if (uni->update.flag)
    fclose(uni->update.fp);

  destroy_workspace();

  destroy_globals();

  fprintf(stderr, "safemem %d\n", safememcurrcount());

  exit(0);
}

//========================================================================
// commandline processing

PRIVATE struct option long_options[] = {
  {"verbose",       no_argument,       0,  0},
  {"spectrum",      no_argument,       0,  1},
  {"metering",      no_argument,       0,  2},
  {"load",          required_argument, 0,  3},
  {"mode",          required_argument, 0,  4},
  {"buffsize",      required_argument, 0,  5},
  {"ringmult",      required_argument, 0,  6},
  {"blowr-path",    required_argument, 0,  7},
  {"meter-path",    required_argument, 0,  8},
  {"client-name",   required_argument, 0,  9},
  {"command-path",  required_argument, 0, 10},
  {"init-path",     required_argument, 0, 11},
  {"replay-path",   required_argument, 0, 12},
  {"spectrum-path", required_argument, 0, 13},
  {"wisdom-path",   required_argument, 0, 14},
  {"echo-path",     required_argument, 0, 15},
  {"skewoffs",      required_argument, 0, 16},
  {"help",          no_argument,       0, 99},
  {0,               0,                 0,  0}
};
PRIVATE char *short_options = "vmsl:h?";
PRIVATE int option_index;

PRIVATE void usage(void);

PRIVATE void
setup_from_commandline(int argc, char **argv) {
  int c;
  while ((c = getopt_long(argc, argv,
			  short_options,
			  long_options,
			  &option_index)) != EOF) {
    switch (c) {
    case 0:
    case 'v':
      top->verbose = TRUE;
      break;

    case 1:
    case 's':
      uni->spec.flag = TRUE;
      break;

    case 2:
    case 'm':
      uni->meter.flag = TRUE;
      break;

    case 3:
    case 'l':
      strcpy(loc.path.rcfile, optarg);
      break;

    case 4:
      loc.def.mode = atoi(optarg);
      break;

    case 5:
      loc.def.size = atoi(optarg);
      break;

    case 6:
      loc.mult.ring = atoi(optarg);
      break;

    case 7:
      strcpy(loc.path.blowr, optarg);
      break;

    case 8:
      strcpy(loc.path.meter, optarg);
      break;

    case 9:
      strcpy(loc.name, optarg);
      break;

    case 10:
      strcpy(loc.path.parm, optarg);
      break;

    case 11:
      strcpy(loc.path.rcfile, optarg);
      break;

    case 12:
      strcpy(loc.path.replay, optarg);
      break;

    case 13:
      strcpy(loc.path.spec, optarg);
      break;

    case 14:
      strcpy(loc.path.wisdom, optarg);
      break;

    case 15:
      strcpy(loc.path.echo, optarg);
      break;

    case 16:
      loc.skew.offs = atoi(optarg);
      break;

    case 99:
    case 'h':
    default:
      usage();
    }
  }
}  

//========================================================================

PRIVATE void
create_globals(void) {
  int i;
  top = (struct _top *) safealloc(1, sizeof(struct _top), "top global");
  uni = (struct _uni *) safealloc(1, sizeof(struct _uni), "uni global");
  for (i = 0; i < MAXRX; i++)
    rx[i] = (struct _rx *) safealloc(1, sizeof(struct _rx), "rx global");
  tx = (struct _tx *) safealloc(1, sizeof(struct _tx), "tx global");
}

PRIVATE void
setup(int argc, char **argv) {
  create_globals();

  top->pid = getpid();
  top->uid = getuid();
  top->start_tv = now_tv();
  top->running = TRUE;
  top->verbose = FALSE;
  top->state = RUN_PLAY;
  top->offs = DEFOFFS;
  top->jack.doin = FALSE;
  top->jack.acon = FALSE;
  top->jack.rsiz = DEFSIZE;

  fprintf(stderr, "safemem %d\n", safememcurrcount());
  safememreset();

  setup_defaults();

  setup_from_commandline(argc, argv);

  setup_workspace(loc.def.rate,
		  loc.def.size,
		  loc.def.mode,
		  loc.path.wisdom,
		  loc.def.spec,
		  loc.def.nrx,
		  loc.def.comp);

  setup_updates();

  setup_local_audio();
  setup_system_audio();

  setup_threading();

  reset_meters();
  reset_spectrum();
  reset_counters();
}

//========================================================================

int 
main(int argc, char **argv) { setup(argc, argv), execute(), closeup(); } 

PRIVATE void
usage(void) {
  fprintf(stderr, "--verbose\n");
  fprintf(stderr, " -v\n");
  fprintf(stderr, "	Turn on verbose mode (echo commands, etc.)\n");
  fprintf(stderr, "--spectrum\n");
  fprintf(stderr, " -s\n");
  fprintf(stderr, "	Turn on spectrum computation\n");
  fprintf(stderr, "--metering\n");
  fprintf(stderr, " -m\n");
  fprintf(stderr, "	Turn on meter computation\n");
  fprintf(stderr, "--load=<load-file>\n");
  fprintf(stderr, " -l <load-file>\n");
  fprintf(stderr, "	Read update commands from <load-file> at startup\n");
  fprintf(stderr, "--mode=<mode>\n");
  fprintf(stderr, "	Start radio in mode <mode>\n");
  fprintf(stderr, "--buffsize=<power-of-2>\n");
  fprintf(stderr, "	Use <power-of-2> as DSP buffersize\n");
  fprintf(stderr, "--ringmult=<num>\n");
  fprintf(stderr, "	Use <num> * <buffsize> for ring buffer length\n");
  fprintf(stderr, "--blowr-path=<path>\n");
  fprintf(stderr, "	Write audio-subsystem error monitor output to <path>\n");
  fprintf(stderr, "--meter-path=<pipe-path>\n");
  fprintf(stderr, "	Use named pipe <pipe-path> as conduit for meter data\n");
  fprintf(stderr, "--client-name=<your-preference>\n");
  fprintf(stderr, "	Name the DttSP jack client anything you like\n");
  fprintf(stderr, "--command-path=<pipe-path>\n");
  fprintf(stderr, "	Use named pipe <pipe-path> as a conduit for update commands\n");
  fprintf(stderr, "--init-path=<init-file>\n");
  fprintf(stderr, "	Read update commands from <init-file> at startup. Like -l.\n");
  fprintf(stderr, "--replay-path=<path>\n");
  fprintf(stderr, "	Write/reread saved update commands to/from <path>\n");
  fprintf(stderr, "--spectrum-path=<pipe-path>\n");
  fprintf(stderr, "	Use named pipe <pipe-path> as conduit for spectrum data\n");
  fprintf(stderr, "--wisdom-path=<path>\n");
  fprintf(stderr, "	fftw3 wisdom is in <path>\n");
  fprintf(stderr, "--echo-path=<path>\n");
  fprintf(stderr, "	Write update command processor output to <path>\n");
  fprintf(stderr, "--skewoffs=<+/-num>\n");
  fprintf(stderr, "	Correct for audio channel skew by num\n");
  fprintf(stderr, "--help\n");
  fprintf(stderr, " -h\n");
  fprintf(stderr, "	Write this message and exit.\n");

  exit(1);
}  
