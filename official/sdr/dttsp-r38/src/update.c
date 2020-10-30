/* update.c

common defs and code for parm update 
   
This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2004, 2005, 2006-5 by Frank Brickle, AB2KT and Bob McGwier, N4HY

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

#include <common.h>

////////////////////////////////////////////////////////////////////////////
// for commands affecting RX, which RX is Listening

#define RL (uni->multirx.lis)

////////////////////////////////////////////////////////////////////////////

PRIVATE REAL INLINE
dB2lin(REAL dB) { return pow(10.0, dB / 20.0); }

PRIVATE int
setRXFilter(int n, char **p) {
  REAL low_frequency = atof(p[0]),
       high_frequency = atof(p[1]);
  int i, ncoef = uni->buflen + 1, fftlen = 2 * uni->buflen;
  fftwf_plan ptmp;
  COMPLEX *zcvec;

  if (fabs(low_frequency) >= 0.5 * uni->samplerate)
    return -1;
  if (fabs(high_frequency) >= 0.5 * uni->samplerate)
    return -2;
  if ((low_frequency + 10) >= high_frequency)
    return -3;
  delFIR_COMPLEX(rx[RL]->filt.coef);

  rx[RL]->filt.coef = newFIR_Bandpass_COMPLEX(low_frequency,
					     high_frequency,
					     uni->samplerate, ncoef);

  zcvec = newvec_COMPLEX(fftlen, "filter z vec in setFilter");
  ptmp = fftwf_plan_dft_1d(fftlen,
			   (fftwf_complex *) zcvec,
			   (fftwf_complex *) rx[RL]->filt.ovsv->zfvec,
			   FFTW_FORWARD, uni->wisdom.bits);
#ifdef LHS
  for (i = 0; i < ncoef; i++)
    zcvec[i] = rx[RL]->filt.coef->coef[i];
#else
  for (i = 0; i < ncoef; i++)
    zcvec[fftlen - ncoef + i] = rx[RL]->filt.coef->coef[i];
#endif
  fftwf_execute(ptmp);
  fftwf_destroy_plan(ptmp);
  delvec_COMPLEX(zcvec);
  normalize_vec_COMPLEX(rx[RL]->filt.ovsv->zfvec, rx[RL]->filt.ovsv->fftlen);
  memcpy((char *) rx[RL]->filt.save, (char *) rx[RL]->filt.ovsv->zfvec,
	 rx[RL]->filt.ovsv->fftlen * sizeof(COMPLEX));

  return 0;
}

PRIVATE int
setTXFilter(int n, char **p) {
  REAL low_frequency = atof(p[0]),
       high_frequency = atof(p[1]);
  int i, ncoef = uni->buflen + 1, fftlen = 2 * uni->buflen;
  fftwf_plan ptmp;
  COMPLEX *zcvec;

  if (fabs(low_frequency) >= 0.5 * uni->samplerate)
    return -1;
  if (fabs(high_frequency) >= 0.5 * uni->samplerate)
    return -2;
  if ((low_frequency + 10) >= high_frequency)
    return -3;
  delFIR_COMPLEX(tx->filt.coef);
  tx->filt.coef = newFIR_Bandpass_COMPLEX(low_frequency,
					 high_frequency,
					 uni->samplerate, ncoef);

  zcvec = newvec_COMPLEX(fftlen, "filter z vec in setFilter");
  ptmp = fftwf_plan_dft_1d(fftlen,
			   (fftwf_complex *) zcvec,
			   (fftwf_complex *) tx->filt.ovsv->zfvec,
			   FFTW_FORWARD, uni->wisdom.bits);

#ifdef LHS
  for (i = 0; i < ncoef; i++)
    zcvec[i] = tx->filt.coef->coef[i];
#else
  for (i = 0; i < ncoef; i++)
    zcvec[fftlen - ncoef + i] = tx->filt.coef->coef[i];
#endif
  fftwf_execute(ptmp);
  fftwf_destroy_plan(ptmp);
  delvec_COMPLEX(zcvec);
  normalize_vec_COMPLEX(tx->filt.ovsv->zfvec, tx->filt.ovsv->fftlen);
  memcpy((char *) tx->filt.save,
	 (char *) tx->filt.ovsv->zfvec,
	 tx->filt.ovsv->fftlen * sizeof(COMPLEX));

  return 0;
}

PRIVATE int
setFilter(int n, char **p) {
  if (n == 2)
    return setRXFilter(n, p);
  else {
    int trx = atoi(p[2]);
    if (trx == RX)
      return setRXFilter(n, p);
    else if (trx == TX)
      return setTXFilter(n, p);
    else
      return -1;
  }
}

// setMode <mode> [TRX]
PRIVATE int
setMode(int n, char **p) {
  int mode = atoi(p[0]);
  if (n > 1) {
    int trx = atoi(p[1]);
    switch (trx) {
    case TX:
      tx->mode = mode;
      break;
    case RX:
    default:
      rx[RL]->mode = mode;
      break;
    }
  } else
    tx->mode = rx[RL]->mode = uni->mode.sdr = mode;
  if (rx[RL]->mode == AM)
    rx[RL]->am.gen->mode = AMdet;
  if (rx[RL]->mode == SAM)
    rx[RL]->am.gen->mode = SAMdet;
  return 0;
}

PRIVATE int
setOsc(int n, char **p) {
  double newfreq = atof(p[0]);
  if (fabs(newfreq) >= 0.5 * uni->samplerate)
    return -1;
  newfreq *= 2.0 * M_PI / uni->samplerate;
  if (n > 1) {
    int trx = atoi(p[1]);
    switch (trx) {
    case TX:
      tx->osc.gen->Frequency = newfreq;
      break;
    case RX:
    default:
      rx[RL]->osc.gen->Frequency = newfreq;
      break;
    }
  } else
    tx->osc.gen->Frequency = rx[RL]->osc.gen->Frequency = newfreq;
  return 0;
}

PRIVATE void
replay_updates(void) {
  char _str[4096], *str = _str;
  splitfld _splt, *splt = &_splt;
  BOOLEAN quiet = FALSE;
  extern CTE update_cmds[];
  FILE *log;

  log = top->verbose ? stderr : 0;

  // left back at end after rewind
  // and subsequent reads
  rewind(uni->update.fp);

  while (fgets(str, 4096, uni->update.fp)) {

    // echo to logging output?
    if (*str == '-') {
      quiet = TRUE;
      str++;
    } else
      quiet = FALSE;

    split(splt, str);
    if (NF(splt) < 1)
      continue;

    else {
      Thunk thk = Thunk_lookup(update_cmds, F(splt, 0));
      if (!thk)
	continue;

      else {
	int val = (*thk) (NF(splt) - 1, Fptr(splt, 1));

	if (log && !quiet) {
	  int i;
	  char *s = since(&top->start_tv);
	  fprintf(log, "replay[%s]: returned %d from", s, val);
	  for (i = 0; i < NF(splt); i++)
	    fprintf(log, " %s", F(splt, i));
	  putc('\n', log);
	  fflush(log);
	}
	// discard val
      }
    }
  }
}

PRIVATE int
setBlkNR(int n, char **p) {
  rx[RL]->banr.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setBlkNRval(int n, char **p) {
  REAL adaptation_rate = atof(p[0]);
  rx[RL]->banr.gen->adaptation_rate = adaptation_rate;
  return 0;
}

PRIVATE int
setBlkANF(int n, char **p) {
  rx[RL]->banf.flag = atoi(p[0]);
  return 0;
}
PRIVATE int
setBlkANFval(int n, char **p) {
  REAL adaptation_rate = atof(p[0]);
  rx[RL]->banf.gen->adaptation_rate = adaptation_rate;
  return 0;
}

PRIVATE int
setNB(int n, char **p) {
  rx[RL]->nb.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setNBvals(int n, char **p) {
  REAL threshold = atof(p[0]);
  rx[RL]->nb.gen->threshold = rx[RL]->nb.thresh = threshold;
  return 0;
}

PRIVATE int
setSDROM(int n, char **p) {
  rx[RL]->nb_sdrom.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setSDROMvals(int n, char **p) {
  REAL threshold = atof(p[0]);
  rx[RL]->nb_sdrom.gen->threshold = rx[RL]->nb_sdrom.thresh = threshold;
  return 0;
}

PRIVATE int
setBIN(int n, char **p) {
  rx[RL]->bin.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setfixedAGC(int n, char **p) {
  REAL gain = atof(p[0]);
  if (n > 1) {
    int trx = atoi(p[1]);
    switch (trx) {
    case TX:
      tx->leveler.gen->gain.now = gain;
      break;
    case RX:
    default:
      rx[RL]->dttspagc.gen->gain.now = gain;
      break;
    }
  } else
    tx->leveler.gen->gain.now = rx[RL]->dttspagc.gen->gain.now = gain;
  return 0;
}

PRIVATE int
setRXAGCCompression(int n, char **p) {
  REAL rxcompression = atof(p[0]);
  rx[RL]->dttspagc.gen->gain.top = pow(10.0, rxcompression * 0.05);
  return 0;
}

PRIVATE int
setTXALCAttack(int n, char **p) {
  REAL tmp = atof(p[0]);
  tx->alc.gen->attack = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  tx->alc.gen->one_m_attack = exp(-1000.0 / (tmp * uni->samplerate));
  tx->alc.gen->sndx =
    (tx->alc.gen->indx + (int) (0.003 * uni->samplerate * tmp)) & tx->alc.gen->mask;
  tx->alc.gen->fastindx =
    (tx->alc.gen->sndx + FASTLEAD * tx->alc.gen->mask) & tx->alc.gen->mask;
  tx->alc.gen->fasthangtime = 0.1;
  return 0;
}

PRIVATE int
setTXALCDecay(int n, char **p) {
  REAL tmp = atof(p[0]);
  tx->alc.gen->decay = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  tx->alc.gen->one_m_decay = exp(-1000.0 / (tmp * uni->samplerate));
  return 0;
}

PRIVATE int
setTXALCHang(int n, char **p) {
  REAL hang = atof(p[0]);
  tx->alc.gen->hangtime = 0.001 * hang;
  return 0;
}

PRIVATE int
setTXALCBot(int n, char **p) {
  REAL bot = atof(p[0]);
  tx->alc.gen->gain.bottom = bot;
  return 0;
}

PRIVATE int
setTXLevelerAttack(int n, char **p) {
  REAL tmp = atof(p[0]);
  tx->leveler.gen->attack = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  tx->leveler.gen->one_m_attack = exp(-1000.0 / (tmp * uni->samplerate));
  tx->leveler.gen->sndx =
    (tx->leveler.gen->indx +
     (int) (0.003 * uni->samplerate * tmp)) & tx->leveler.gen->mask;
  tx->leveler.gen->fastindx =
    (tx->leveler.gen->sndx +
     FASTLEAD * tx->leveler.gen->mask) & tx->leveler.gen->mask;
  tx->leveler.gen->fasthangtime = 0.1;	//wa6ahl: 100 ms
  return 0;
}

PRIVATE int
setTXLevelerSt(int n, char **p) {
  BOOLEAN tmp = atoi(p[0]);
  tx->leveler.flag = tmp;
  return 0;
}

PRIVATE int
setTXLevelerDecay(int n, char **p) {
  REAL tmp = atof(p[0]);
  tx->leveler.gen->decay = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  tx->leveler.gen->one_m_decay = exp(-1000.0 / (tmp * uni->samplerate));
  return 0;
}

PRIVATE int
setTXLevelerTop(int n, char **p) {
  REAL top = atof(p[0]);
  tx->leveler.gen->gain.top = top;
  return 0;
}

PRIVATE int
setTXLevelerHang(int n, char **p) {
  REAL hang = atof(p[0]);
  tx->leveler.gen->hangtime = 0.001 * hang;
  return 0;
}

PRIVATE int
setRXAGC(int n, char **p) {
  int setit = atoi(p[0]);
  rx[RL]->dttspagc.gen->mode = 1;
  rx[RL]->dttspagc.gen->attack = 1.0 - exp(-1000 / (2.0 * uni->samplerate));
  rx[RL]->dttspagc.gen->one_m_attack = 1.0 - rx[RL]->dttspagc.gen->attack;
  rx[RL]->dttspagc.gen->hangindex = rx[RL]->dttspagc.gen->indx = 0;
  rx[RL]->dttspagc.gen->sndx = (int) (uni->samplerate * 0.006f);
  rx[RL]->dttspagc.gen->fastindx = FASTLEAD;
  switch (setit) {
  case agcOFF:
    rx[RL]->dttspagc.gen->mode = agcOFF;
    rx[RL]->dttspagc.flag = TRUE;
    break;
  case agcSLOW:
    rx[RL]->dttspagc.gen->mode = agcSLOW;
    rx[RL]->dttspagc.gen->hangtime = 0.5;
    rx[RL]->dttspagc.gen->fasthangtime = 0.1;
    rx[RL]->dttspagc.gen->decay = 1.0 - exp(-1000 / (500.0 * uni->samplerate));
    rx[RL]->dttspagc.gen->one_m_decay = 1.0 - rx[RL]->dttspagc.gen->decay;
    rx[RL]->dttspagc.flag = TRUE;
    break;
  case agcMED:
    rx[RL]->dttspagc.gen->mode = agcMED;
    rx[RL]->dttspagc.gen->hangtime = 0.25;
    rx[RL]->dttspagc.gen->fasthangtime = 0.1;
    rx[RL]->dttspagc.gen->decay = 1.0 - exp(-1000 / (250.0 * uni->samplerate));
    rx[RL]->dttspagc.gen->one_m_decay = 1.0 - rx[RL]->dttspagc.gen->decay;
    rx[RL]->dttspagc.flag = TRUE;
    break;
  case agcFAST:
    rx[RL]->dttspagc.gen->mode = agcFAST;
    rx[RL]->dttspagc.gen->hangtime = 0.1;
    rx[RL]->dttspagc.gen->fasthangtime = 0.1;
    rx[RL]->dttspagc.gen->hangtime = 0.1;
    rx[RL]->dttspagc.gen->decay = 1.0 - exp(-1000 / (100.0 * uni->samplerate));
    rx[RL]->dttspagc.gen->one_m_decay = 1.0 - rx[RL]->dttspagc.gen->decay;
    rx[RL]->dttspagc.flag = TRUE;
    break;
  case agcLONG:
    rx[RL]->dttspagc.gen->mode = agcLONG;
    rx[RL]->dttspagc.flag = TRUE;
    rx[RL]->dttspagc.gen->hangtime = 0.75;
    rx[RL]->dttspagc.gen->fasthangtime = 0.1;
    rx[RL]->dttspagc.gen->decay = 1.0 - exp(-0.5 / uni->samplerate);
    rx[RL]->dttspagc.gen->one_m_decay = 1.0 - rx[RL]->dttspagc.gen->decay;
    break;
  }
  return 0;
}

PRIVATE int
setRXAGCAttack(int n, char **p) {
  REAL tmp = atof(p[0]);
  rx[RL]->dttspagc.gen->mode = 1;
  rx[RL]->dttspagc.gen->hangindex = rx[RL]->dttspagc.gen->indx = 0;
  rx[RL]->dttspagc.gen->sndx = (int) (uni->samplerate * 0.006);
  rx[RL]->dttspagc.gen->fasthangtime = 0.1;
  rx[RL]->dttspagc.gen->fastindx = FASTLEAD;
  rx[RL]->dttspagc.gen->attack = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  rx[RL]->dttspagc.gen->one_m_attack = exp(-1000.0 / (tmp * uni->samplerate));
  rx[RL]->dttspagc.gen->sndx = (int) (uni->samplerate * tmp * 0.003);
  return 0;
}

PRIVATE int
setRXAGCDecay(int n, char **p) {
  REAL tmp = atof(p[0]);
  rx[RL]->dttspagc.gen->decay = 1.0 - exp(-1000.0 / (tmp * uni->samplerate));
  rx[RL]->dttspagc.gen->one_m_decay = exp(-1000.0 / (tmp * uni->samplerate));
  return 0;
}

PRIVATE int
setRXAGCHang(int n, char **p) {
  REAL hang = atof(p[0]);
  rx[RL]->dttspagc.gen->hangtime = 0.001 * hang;
  return 0;
}

PRIVATE int
setRXAGCSlope(int n, char **p) {
  REAL slope = atof(p[0]);
  rx[RL]->dttspagc.gen->slope = dB2lin(0.1 * slope);
  return 0;
}

PRIVATE int
setRXAGCHangThreshold(int h, char **p) {
  REAL hangthreshold = atof(p[0]);
  rx[RL]->dttspagc.gen->hangthresh = 0.01 * hangthreshold;
  return 0;
}

PRIVATE int
setRXAGCLimit(int n, char **p) {
  REAL limit = atof(p[0]);
  rx[RL]->dttspagc.gen->gain.top = limit;
  return 0;
}

PRIVATE int
setRXAGCTop(int n, char **p) {
  REAL top = atof(p[0]);
  rx[RL]->dttspagc.gen->gain.top = top;
  return 0;
}

PRIVATE int
setRXAGCFix(int n, char **p) {
  rx[RL]->dttspagc.gen->gain.fix = atof(p[0]);
  return 0;
}

PRIVATE int
setTXAGCFF(int n, char **p) {
  tx->spr.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setTXAGCFFCompression(int n, char **p) {
  REAL txcompression = atof(p[0]);
  tx->spr.gen->MaxGain =
    (((0.0000401002 * txcompression) - 0.0032093390) * txcompression + 0.0612862687) * txcompression + 0.9759745718;
  return 0;
}

PRIVATE int
setTXAGCLimit(int n, char **p) {
  REAL limit = atof(p[0]);
  tx->alc.gen->gain.top = limit;
  return 0;
}

PRIVATE int
setTXSpeechCompression(int n, char **p) {
  tx->spr.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setTXSpeechCompressionGain(int n, char **p) {
  tx->spr.gen->MaxGain = dB2lin(atof(p[0]));
  return 0;
}

#if 0
PRIVATE int
f2x(REAL f) {
  REAL fix = tx->filt.ovsv->fftlen * f / uni->samplerate;
  return (int) (fix + 0.5);
}
#endif 

PRIVATE int
setGrphRXEQ(int n, char **p) {
  if (n < 4)
    return 0;
  else {
    int i;
    fftwf_plan ptmp;
    COMPLEX *filtcoef, *tmpcoef;
    ComplexFIR tmpfilt;
    REAL preamp, gain[3];

    filtcoef = newvec_COMPLEX(512, "filter for EQ");
    tmpcoef = newvec_COMPLEX(257, "tmp filter for EQ");

    preamp  = dB2lin(atof(p[0])) * 0.5;
    gain[0] = dB2lin(atof(p[1])) * preamp;
    gain[1] = dB2lin(atof(p[2])) * preamp;
    gain[2] = dB2lin(atof(p[3])) * preamp;

    tmpfilt = newFIR_Bandpass_COMPLEX(-400, 400, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cscl(tmpfilt->coef[i], gain[0]);
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(400, 1500, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[1]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(-1500, -400, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[1]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(1500, 6000, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[2]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(-6000, -1500, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[2]));
    delFIR_Bandpass_COMPLEX(tmpfilt);
    for (i = 0; i < 257; i++)
      filtcoef[254 + i] = tmpcoef[i];
    ptmp = fftwf_plan_dft_1d(512,
			     (fftwf_complex *) filtcoef,
			     (fftwf_complex *) rx[RL]->grapheq.gen->p->zfvec,
			     FFTW_FORWARD,
			     uni->wisdom.bits);

    fftwf_execute(ptmp);
    fftwf_destroy_plan(ptmp);
    delvec_COMPLEX(filtcoef);
    delvec_COMPLEX(tmpcoef);
  }

  return 0;
}

PRIVATE int
setGrphTXEQ(int n, char **p) {
  if (n < 4)
    return 0;
  else {
    int i;
    fftwf_plan ptmp;
    COMPLEX *filtcoef, *tmpcoef;
    ComplexFIR tmpfilt;
    REAL preamp, gain[3];

    filtcoef = newvec_COMPLEX(512, "filter for EQ");
    tmpcoef = newvec_COMPLEX(257, "tmp filter for EQ");

    preamp  = dB2lin(atof(p[0])) * 0.5;
    gain[0] = dB2lin(atof(p[1])) * preamp;
    gain[1] = dB2lin(atof(p[2])) * preamp;
    gain[2] = dB2lin(atof(p[3])) * preamp;

    tmpfilt = newFIR_Bandpass_COMPLEX(-400, 400, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cscl(tmpfilt->coef[i], gain[0]);
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(400, 1500, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[1]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(-1500, -400, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[1]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(1500, 6000, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[2]));
    delFIR_Bandpass_COMPLEX(tmpfilt);

    tmpfilt = newFIR_Bandpass_COMPLEX(-6000, -1500, uni->samplerate, 257);
    for (i = 0; i < 257; i++)
      tmpcoef[i] = Cadd(tmpcoef[i], Cscl(tmpfilt->coef[i], gain[2]));
    delFIR_Bandpass_COMPLEX(tmpfilt);
    for (i = 0; i < 257; i++)
      filtcoef[255 + i] = tmpcoef[i];

    ptmp = fftwf_plan_dft_1d(512,
			     (fftwf_complex *) filtcoef,
			     (fftwf_complex *) tx->grapheq.gen->p->zfvec,
			     FFTW_FORWARD,
			     uni->wisdom.bits);
    fftwf_execute(ptmp);

    fftwf_destroy_plan(ptmp);
    delvec_COMPLEX(filtcoef);
  }

  return 0;
}

PRIVATE int
setNotch160(int n, char **p) {
  tx->grapheq.gen->notchflag = atoi(p[0]);
  return 0;
}

PRIVATE int
setTXCarrierLevel(int n, char **p) {
  tx->am.carrier_level = atof(p[0]);
  return 0;
}

PRIVATE int
setANF(int n, char **p) {
  rx[RL]->anf.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setANFvals(int n, char **p) {
  int taps = atoi(p[0]), delay = atoi(p[1]);
  REAL gain = atof(p[2]), leak = atof(p[3]);
  rx[RL]->anf.gen->adaptive_filter_size = taps;
  rx[RL]->anf.gen->delay = delay;
  rx[RL]->anf.gen->adaptation_rate = gain;
  rx[RL]->anf.gen->leakage = leak;
  return 0;
}

PRIVATE int
setNR(int n, char **p) {
  rx[RL]->anr.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setNRvals(int n, char **p) {
  int taps = atoi(p[0]), delay = atoi(p[1]);
  REAL gain = atof(p[2]), leak = atof(p[3]);
  rx[RL]->anr.gen->adaptive_filter_size = taps;
  rx[RL]->anr.gen->delay = delay;
  rx[RL]->anr.gen->adaptation_rate = gain;
  rx[RL]->anr.gen->leakage = leak;
  return 0;
}

PRIVATE int
setcorrectIQ(int n, char **p) {
  REAL phaseadjustment = atof(p[0]),
    gainadjustment = atof(p[1]);
  rx[RL]->iqfix->phase = 0.001 * phaseadjustment;
  rx[RL]->iqfix->gain = 1.0 + 0.001 * gainadjustment;
  return 0;
}

PRIVATE int
setcorrectIQphase(int n, char **p) {
  REAL phaseadjustment = atof(p[0]);
  rx[RL]->iqfix->phase = 0.001 *phaseadjustment;
  return 0;
}

PRIVATE int
setcorrectIQgain(int n, char **p) {
  REAL gainadjustment = atof(p[0]);
  rx[RL]->iqfix->gain = (1.0 + 0.001 * gainadjustment);
  return 0;
}

PRIVATE int
setcorrectTXIQ(int n, char **p) {
  REAL phaseadjustment = atof(p[0]),
    gainadjustment = atof(p[1]);
  tx->iqfix->phase = 0.001 * phaseadjustment;
  tx->iqfix->gain = 1.0 + 0.001 * gainadjustment;
  return 0;
}

PRIVATE int
setcorrectTXIQphase(int n, char **p) {
  REAL phaseadjustment = atof(p[0]);
  tx->iqfix->phase = 0.001 * phaseadjustment;
  return 0;
}

PRIVATE int
setcorrectTXIQgain(int n, char **p) {
  REAL gainadjustment = atof(p[0]);
  tx->iqfix->gain = 1.0 + 0.001 * gainadjustment;
  return 0;
}

PRIVATE int
setSquelch(int n, char **p) {
  rx[RL]->squelch.thresh = atof(p[0]);
  return 0;
}

PRIVATE int
setSquelchSt(int n, char **p) {
  rx[RL]->squelch.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setTXSquelch(int n, char **p) {
  tx->squelch.thresh = atof(p[0]);
  return 0;
}

PRIVATE int
setTXSquelchSt(int n, char **p) {
  tx->squelch.flag = atoi(p[0]);
  return 0;
}

PRIVATE int
setTRX(int n, char **p) {
  uni->mode.trx = atoi(p[0]);
  return 0;
}

PRIVATE int
setRunState(int n, char **p) {
  RUNMODE rs = (RUNMODE) atoi(p[0]);
  top->state = rs;
  return 0;
}

PRIVATE int
setSpotToneVals(int n, char **p) {
  REAL gain = atof(p[0]),
       freq = atof(p[1]),
       rise = atof(p[2]),
       fall = atof(p[3]);
  setSpotToneGenVals(rx[RL]->spot.gen, gain, freq, rise, fall);
  return 0;
}

PRIVATE int
setSpotTone(int n, char **p) {
  if (atoi(p[0])) {
    SpotToneOn(rx[RL]->spot.gen);
    rx[RL]->spot.flag = TRUE;
  } else
    SpotToneOff(rx[RL]->spot.gen);
  return 0;
}

PRIVATE int
setFinished(int n, char **p) {
  top->running = FALSE;
  pthread_exit(0);
  return 0;
}

#if 0
// next-trx-mode [nbufs-to-zap]
PRIVATE int
setSWCH(int n, char **p) {
  top->swch.trx.next = atoi(p[0]);
  if (n > 1)
    top->swch.bfct.want = atoi(p[1]);
  else
    top->swch.bfct.want = 0;
  top->swch.bfct.have = 0;
  if (top->state != RUN_SWCH)
    top->swch.run.last = top->state;
  top->state = RUN_SWCH;
  return 0;
}
#endif
 
// next-trx-mode fall-msec stdy-msec rise-msec
PRIVATE int
setSWCH(int n, char **p) {
  if (n < 4)
    return -1;
  else {
    int  nextrx = atoi(p[0]);
    REAL fallms = atof(p[1]),
         stdyms = atof(p[2]),
         risems = atof(p[3]);

    top->swch.trx.next = nextrx;

    top->swch.env.fall.size = uni->samplerate * fallms / 1e3 + 0.5;
    if (top->swch.env.fall.size > 1)
      top->swch.env.fall.incr = -1.0 / (top->swch.env.fall.size - 1);
    else
      top->swch.env.fall.incr = -1.0;

    top->swch.env.stdy.size = uni->samplerate * stdyms / 1e3 + 0.5;
    top->swch.env.stdy.incr = 0.0;

    top->swch.env.rise.size = uni->samplerate * risems / 1e3 + 0.5;
    if (top->swch.env.rise.size > 1)
      top->swch.env.rise.incr = 1.0 / (top->swch.env.rise.size - 1);
    else
      top->swch.env.rise.incr = 1.0;

    top->swch.env.curr.type = SWCH_FALL;
    top->swch.env.curr.cnt = 0;
    top->swch.env.curr.val = 1.0;

    if (top->state != RUN_SWCH)
      top->swch.run.last = top->state;
    top->state = RUN_SWCH;
    return 0;
  }
}

PRIVATE int
setMonDump(int n, char **p) {
  sem_post(&top->sync.mon.sem);
  return 0;
}

PRIVATE int
setRingBufferOffset(int n, char **p) {
  top->offs = atoi(p[0]);
  top->jack.doin = TRUE;
  return 0;
}

PRIVATE int
setRingBufferReset(int n, char **p) {
  top->jack.doin = TRUE;
  return 0;
}

PRIVATE int
setJackResetSize(int n, char **p) {
  top->jack.rsiz = atoi(p[0]);
  top->jack.doin = TRUE;
  return 0;
}

PRIVATE int
setRXListen(int n, char **p) {
  int lis = atoi(p[0]);
  if (lis < 0 || lis >= uni->multirx.nrx)
    return -1;
  else {
    uni->multirx.lis = lis;
    return 0;
  }
}

PRIVATE int
setRXOn(int n, char **p) {
  if (n < 1) {
    if (uni->multirx.act[RL])
      return -1;
    else {
      uni->multirx.act[RL] = TRUE;
      uni->multirx.nac++;
      rx[RL]->tick = 0;
      return 0;
    }
  } else {
    int k = atoi(p[0]);
    if (k < 0 || k >= uni->multirx.nrx)
      return -1;
    else {
      if (uni->multirx.act[k])
	return -1;
      else {
	uni->multirx.act[k] = TRUE;
	uni->multirx.nac++;
	rx[k]->tick = 0;
	return 0;
      }
    }
  }
}

PRIVATE int
setRXOff(int n, char **p) {
  if (n < 1) {
    if (!uni->multirx.act[RL])
      return -1;
    else {
      uni->multirx.act[RL] = FALSE;
      --uni->multirx.nac;
      return 0;
    }
  } else {
    int k = atoi(p[0]);
    if (k < 0 || k >= uni->multirx.nrx)
      return -1;
    else {
      if (!uni->multirx.act[k])
	return -1;
      else {
	uni->multirx.act[k] = FALSE;
	--uni->multirx.nac;
	return 0;
      }
    }
  }
}

// [pos]  0.0 <= pos <= 1.0
PRIVATE int
setRXPan(int n, char **p) {
  REAL pos, theta;
  if (n < 1) {
    pos = 0.5;
    theta = (1.0 - pos) * M_PI / 2.0;
    rx[RL]->azim = Cmplx(cos(theta), sin(theta));
    return 0;
  } else {
    if ((pos = atof(p[0])) < 0.0 || pos > 1.0)
      return -1;
    theta = (1.0 - pos) * M_PI / 2.0;
    rx[RL]->azim = Cmplx(cos(theta), sin(theta));
    return 0;
  }
}

PRIVATE int
setAuxMixSt(int n, char **p) {
  if (n < 1) {
    uni->mix.rx.flag = uni->mix.tx.flag = FALSE;
    return 0;
  } else {
    BOOLEAN flag = atoi(p[0]);
    if (n > 1) {
      switch (atoi(p[1])) {
      case TX:
	uni->mix.tx.flag = flag;
	break;
      case RX:
      default:
	uni->mix.rx.flag = flag;
	break;
      }
    } else
      uni->mix.rx.flag = uni->mix.tx.flag = flag;
    return 0;
  }
}

// [dB] NB both channels
PRIVATE int
setAuxMixGain(int n, char **p) {
  if (n < 1) {
    uni->mix.rx.gain = uni->mix.tx.gain = 1.0;
    return 0;
  } else {
    REAL gain = dB2lin(atof(p[0]));
    if (n > 1) {
      switch (atoi(p[1])) {
      case TX:
	uni->mix.tx.gain = gain;
	break;
      case RX:
      default:
	uni->mix.rx.gain = gain;
	break;
      }
    } else
      uni->mix.rx.gain = uni->mix.tx.gain = gain;
    return 0;
  }
}

PRIVATE int
setCompandSt(int n, char **p) {
  if (n < 1) {
    tx->cpd.flag = FALSE;
    return 0;
  } else {
    BOOLEAN flag = atoi(p[0]);
    if (n > 1) {
      switch (atoi(p[1])) {
      case RX:
	rx[RL]->cpd.flag = flag;
	break;
      case TX:
      default:
	tx->cpd.flag = flag;
	break;
      }
    } else
      tx->cpd.flag = flag;
    return 0;
  }
}

PRIVATE int
setCompand(int n, char **p) {
  if (n < 1)
    return -1;
  else {
    REAL fac = atof(p[0]);
    if (n > 1) {
      switch (atoi(p[1])) {
      case RX:
	WSCReset(rx[RL]->cpd.gen, fac);
	break;
      case TX:
      default:
	WSCReset(tx->cpd.gen, fac);
	break;
      }
    } else
      WSCReset(tx->cpd.gen, fac);
    return 0;
  }
}

PRIVATE int
setGrphTXEQcmd(int n, char **p) {
  if (n < 1) {
    tx->grapheq.flag = FALSE;
    return 0;
  } else {
    BOOLEAN flag = atoi(p[0]);
    tx->grapheq.flag = flag;
  }
  return 0;
}


PRIVATE int
setGrphRXEQcmd(int n, char **p) {
  if (n < 1) {
    rx[RL]->grapheq.flag = FALSE;
    return 0;
  } else {
    BOOLEAN flag = atoi(p[0]);
    rx[RL]->grapheq.flag = flag;
  }
  return 0;
}

PRIVATE int
setTXCompandSt(int n, char **p) {
  if (n < 1) {
    tx->cpd.flag = FALSE;
    return 0;
  } else {
    BOOLEAN flag = atoi(p[0]);
    tx->cpd.flag = flag;
  }
  return 0;
}

PRIVATE int
setTXCompand(int n, char **p) {
  if (n < 1)
    return -1;
  else {
    REAL fac = atof(p[0]);
    WSCReset(tx->cpd.gen, fac);
  }
  return 0;
}

//------------------------------------------------------------------------

#if 0
// [type]
PRIVATE int
setMeterType(int n, char **p) {
  if (n < 1)
    uni->meter.rx.type = SIGNAL_STRENGTH;
  else {
    METERTYPE type = (METERTYPE) atoi(p[0]);
    if (n > 1) {
      int trx = atoi(p[1]);
      switch (trx) {
      case TX:
	uni->meter.tx->type = type;
	break;
      case RX:
      default:
	uni->meter.rx.type = type;
	break;
      }
    } else
      uni->meter.rx.type = type;
  }
  return 0;
}
#endif

PRIVATE int
setSpectrumPolyphase(int n, char **p) {
  BOOLEAN setit = atoi(p[0]);
  if (uni->spec.polyphase != setit) {
    if (setit) {
      uni->spec.polyphase = TRUE;
      uni->spec.mask = (8 * uni->spec.size) - 1;
      {
	RealFIR WOLAfir;
	REAL MaxTap = 0;
	int i;
	WOLAfir = newFIR_Lowpass_REAL(1.0,
				      (REAL) uni->spec.size,
				      8 * uni->spec.size - 1);
	memset(uni->spec.window, 0, 8 * sizeof(REAL) * uni->spec.size);
	memcpy(uni->spec.window,
	       FIRcoef(WOLAfir),
	       sizeof(REAL) * (8 * uni->spec.size - 1));
	for (i = 0; i < 8 * uni->spec.size; i++)
	  MaxTap = max(MaxTap, fabs(uni->spec.window[i]));
	MaxTap = 1.0f / MaxTap;
	for (i = 0; i < 8 * uni->spec.size; i++)
	  uni->spec.window[i] *= MaxTap;
	delFIR_REAL(WOLAfir);
      }
    } else {
      uni->spec.polyphase = FALSE;
      uni->spec.mask = uni->spec.size - 1;
      memset(uni->spec.window, 0, sizeof(REAL) * uni->spec.size);
      makewindow(uni->spec.wintype, uni->spec.size - 1, uni->spec.window);
    }
    reinit_spectrum(&uni->spec);
  }
  return 0;
}

PRIVATE int
setSpectrumWindow(int n, char **p) {
  Windowtype window = atoi(p[0]);
  if (!uni->spec.polyphase)
    makewindow(window, uni->spec.size, uni->spec.window);
  uni->spec.wintype = window;
  return 0;
}

PRIVATE int
setSpectrumType(int n, char **p) {
  uni->spec.type = SPEC_POST_FILT;
  uni->spec.scale = SPEC_PWR;
  uni->spec.rxk = RL;
  switch (n) {
  case 3:
    uni->spec.rxk = atoi(p[2]);
  case 2:
    uni->spec.scale = atoi(p[1]);
  case 1:
    uni->spec.type = atoi(p[0]);
    break;
  case 0:
    break;
  default:
    return -1;
  }
  return uni->spec.type;
}

PRIVATE int
setDCBlockSt(int n, char **p) {
  if (n < 1) {
    tx->dcb.flag = FALSE;
    return 0;
  } else {
    tx->dcb.flag = atoi(p[0]);
    return 0;
  }
}

PRIVATE int
setDCBlock(int n, char **p) {
  if (n < 1)
    return -1;
  else {
    resetDCBlocker(tx->dcb.gen, atoi(p[0]));
    return 0;
  }
}

//========================================================================

PRIVATE int
setNewBuflen(int n, char **p) {
  extern int reset_for_buflen(int);
  int rtn = -1;
  if (n == 1) {
    top->susp = TRUE;
    if (reset_for_buflen(atoi(p[0])) != -1) {
      if (uni->update.flag)
	replay_updates();
      rtn = 0;
    }
    top->susp = FALSE;
  }
  return rtn;
}

//========================================================================

// save current state while guarded by upd sem

// reqMeter [label [TRX]]

PRIVATE int
reqMeter(int n, char **p) {
  if (n > 1) {
    int trx = atoi(p[1]);
    switch (trx) {
    case TX:
      snap_meter_tx(&uni->meter, atoi(p[0]));
      break;
    case RX:
    default:
      snap_meter_rx(&uni->meter, atoi(p[0]));
    }
  } else
    snap_meter_rx(&uni->meter, n > 0 ? atoi(p[0]) : 0);
    
  sem_post(&top->sync.mtr.sem);
  return 0;
}

// reqRXMeter [label]

PRIVATE int
reqRXMeter(int n, char **p) {
  snap_meter_rx(&uni->meter, n > 0 ? atoi(p[0]) : 0);
  sem_post(&top->sync.mtr.sem);
  return 0;
}

// reqTXMeter [label]

PRIVATE int
reqTXMeter(int n, char **p) {
  snap_meter_tx(&uni->meter, n > 0 ? atoi(p[0]) : 0);
  sem_post(&top->sync.mtr.sem);
  return 0;
}

// simile modo

PRIVATE int
reqSpectrum(int n, char **p) {
  snap_spectrum(&uni->spec, n > 0 ? atoi(p[0]) : 0);
  sem_post(&top->sync.pws.sem);
  return 0;
}

PRIVATE int
reqScope(int n, char **p) {
  snap_scope(&uni->spec, n > 0 ? atoi(p[0]) : 0);
  sem_post(&top->sync.pws.sem);
  return 0;
}

//========================================================================

CTE update_cmds[] = {
  {"reqMeter", reqMeter},
  {"reqRXMeter", reqRXMeter},
  {"reqTXMeter", reqTXMeter},
  {"reqScope", reqScope},
  {"reqSpectrum", reqSpectrum},
  {"setANF", setANF},
  {"setANFvals", setANFvals},
  {"setAuxMixGain", setAuxMixGain},
  {"setAuxMixSt", setAuxMixSt},
  {"setBIN", setBIN},
  {"setBlkANF", setBlkANF},
  {"setBlkANFval", setBlkANFval},
  {"setBlkNR", setBlkNR},
  {"setBlkNRval", setBlkNRval},
  {"setCompand", setCompand},
  {"setCompandSt", setCompandSt},
  {"setcorrectIQ", setcorrectIQ},
  {"setcorrectIQgain", setcorrectIQgain},
  {"setcorrectIQphase", setcorrectIQphase},
  {"setcorrectTXIQ", setcorrectTXIQ},
  {"setcorrectTXIQgain", setcorrectTXIQgain},
  {"setcorrectTXIQphase", setcorrectTXIQphase},
  {"setDCBlock", setDCBlock},
  {"setDCBlockSt", setDCBlockSt},
  {"setFilter", setFilter},
  {"setFinished", setFinished},
  {"setfixedAGC", setfixedAGC},
  {"setGrphRXEQ", setGrphRXEQ},
  {"setGrphRXEQcmd", setGrphRXEQcmd},
  {"setGrphTXEQ", setGrphTXEQ},
  {"setGrphTXEQcmd", setGrphTXEQcmd},
  {"setJackResetSize", setJackResetSize},
  {"setMode", setMode},
  {"setMonDump", setMonDump},
  {"setNB", setNB},
  {"setNBvals", setNBvals},
  {"setNR", setNR},
  {"setNRvals", setNRvals},
  {"setNewBuflen", setNewBuflen},
  {"setNotch160", setNotch160},
  {"setOsc", setOsc},
  {"setRXAGC", setRXAGC},
  {"setRXAGCAttack", setRXAGCAttack},
  {"setRXAGCCompression", setRXAGCCompression},
  {"setRXAGCCompression", setRXAGCCompression},
  {"setRXAGCDecay", setRXAGCDecay},
  {"setRXAGCFix", setRXAGCFix},
  {"setRXAGCHang", setRXAGCHang},
  {"setRXAGCHangThreshold", setRXAGCHangThreshold},
  {"setRXAGCLimit", setRXAGCLimit},
  {"setRXAGCSlope", setRXAGCSlope},
  {"setRXAGCTop", setRXAGCTop},
  {"setRXListen", setRXListen},
  {"setRXOff", setRXOff},
  {"setRXOn", setRXOn},
  {"setRXPan", setRXPan},
  {"setRingBufferOffset", setRingBufferOffset},
  {"setRingBufferReset", setRingBufferReset},
  {"setRunState", setRunState},
  {"setSDROM", setSDROM},
  {"setSDROMvals", setSDROMvals},
  {"setSWCH", setSWCH},
  {"setSpectrumPolyphase", setSpectrumPolyphase},
  {"setSpectrumType", setSpectrumType},
  {"setSpectrumWindow", setSpectrumWindow},
  {"setSpotTone", setSpotTone},
  {"setSpotToneVals", setSpotToneVals},
  {"setSquelch", setSquelch},
  {"setSquelchSt", setSquelchSt},
  {"setTRX", setTRX},
  {"setTXAGCFF", setTXAGCFF},
  {"setTXAGCFFCompression", setTXAGCFFCompression},
  {"setTXAGCLimit", setTXAGCLimit},
  {"setTXALCAttack", setTXALCAttack},
  {"setTXALCBot", setTXALCBot},
  {"setTXALCDecay", setTXALCDecay},
  {"setTXALCHang", setTXALCHang},
  {"setTXCarrierLevel", setTXCarrierLevel},
  {"setTXCompand", setTXCompand},
  {"setTXCompandSt", setTXCompandSt},
  {"setTXLevelerAttack", setTXLevelerAttack},
  {"setTXLevelerDecay", setTXLevelerDecay},
  {"setTXLevelerHang", setTXLevelerHang},
  {"setTXLevelerSt", setTXLevelerSt},
  {"setTXLevelerTop", setTXLevelerTop},
  {"setTXSpeechCompression", setTXSpeechCompression},
  {"setTXSpeechCompressionGain", setTXSpeechCompressionGain},
  {"setTXSquelch", setTXSquelch},
  {"setTXSquelchSt", setTXSquelchSt},

#if 0
  {"setMeterType", setMeterType},
#endif
  {0, 0}
};

//........................................................................

int
do_update(char *str, FILE *log) {
  BOOLEAN quiet = FALSE;
  SPLIT splt = &uni->update.splt;

  // append to replay file?
  if (*str == '!') {
    str++;			// strip !
    if (uni->update.flag)
      fputs(str, uni->update.fp);
  }
  // echo to logging output?
  if (*str == '-') {
    quiet = TRUE;
    str++;
  }

  split(splt, str);

  if (NF(splt) < 1)
    return -1;

  else {
    Thunk thk = Thunk_lookup(update_cmds, F(splt, 0));
    if (!thk)
      return -1;
    else {
      int val;

      sem_wait(&top->sync.upd.sem);
      val = (*thk)(NF(splt) - 1, Fptr(splt, 1));
      sem_post(&top->sync.upd.sem);

      if (log && !quiet) {
	int i;
	char *s = since(&top->start_tv);
	fprintf(log, "update[%s]: returned %d from", s, val);
	for (i = 0; i < NF(splt); i++)
	  fprintf(log, " %s", F(splt, i));
	putc('\n', log);
	fflush(log);
      }

      return val;
    }
  }
}

//------------------------------------------------------------------------
