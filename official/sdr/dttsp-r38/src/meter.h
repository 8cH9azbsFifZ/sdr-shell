/* meter.h */
/*
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

#ifndef _meter_h
#define _meter_h

#include <fromsys.h>
#include <defs.h>
#include <banal.h>
#include <splitfields.h>
#include <datatypes.h>
#include <bufvec.h>
#include <cxops.h>
#include <ringb.h>
#include <lmadf.h>
#include <fftw3.h>
#include <ovsv.h>
#include <filter.h>
#include <oscillator.h>
#include <dttspagc.h>
#include <am_demod.h>
#include <fm_demod.h>
#include <noiseblanker.h>
#include <correctIQ.h>
#include <speechproc.h>
#include <spottone.h>
#include <update.h>

typedef enum {
  SIGNAL_STRENGTH,
  AVG_SIGNAL_STRENGTH,
  ADC_REAL,
  ADC_IMAG,
  AGC_GAIN,
  MIC,
  PWR,
  ALC,
  EQtap,
  LEVELER,
  COMP,
  CPDR,
  ALC_G,
  LVL_G
} METERTYPE;

#define RXMETERPTS (5)
#define RXMETER_PRE_CONV (0)
#define RXMETER_POST_FILT (1)
#define RXMETER_POST_AGC (2)

#define TXMETERPTS (9)

typedef enum {
  RX_SIGNAL_STRENGTH,
  RX_AVG_SIGNAL_STRENGTH,
  RX_ADC_REAL,
  RX_ADC_IMAG,
  RX_AGC_GAIN
} RXMETERTYPE;

typedef enum {
  TX_MIC,
  TX_PWR,
  TX_ALC,
  TX_EQtap,
  TX_LEVELER,
  TX_COMP,
  TX_CPDR,
  TX_ALC_G,
  TX_LVL_G
} TXMETERTYPE;

typedef struct _meter_block {
  BOOLEAN flag;
  int label, last;
  struct {
    REAL val[MAXRX][RXMETERPTS];
    RXMETERTYPE mode[MAXRX];
  } rx;
  struct {
    REAL val[TXMETERPTS];
    TXMETERTYPE mode;
  } tx;
  struct {
    REAL rx[MAXRX][RXMETERPTS], tx[TXMETERPTS];
  } snap;
} METERBlock;

#define METER_LAST_RX (0)
#define METER_LAST_TX (1)

extern void snap_meter_rx(METERBlock *, int);
extern void snap_meter_tx(METERBlock *, int);

#endif
