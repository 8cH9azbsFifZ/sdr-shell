/***************************************************************************
                          rigctrl.cpp  -  description
                             -------------------
    begin                : Sun Sep 8 2002
    copyright            : (C) 2002 by Luc Langehegermann
    email                : lx2gt@qsl.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "rigctrl.h"

#include <qtimer.h>

rigctrl::rigctrl(QObject *parent, const char *name ) : QObject(parent,name) {
  azcorrection=0;
  elcorrection=0;
  correction=0;
  wrapper = new hamlibWrapper();
  currentSatellite=NULL;
  currentTransponder=NULL;
  currentCorrection=0;
  counter=0;
  currentUplinkFreq=145000000;
  currentDownlinkFreq=435000000;
  oldtrxfreq=0;
  // timer for polling the rig!
  QTimer* timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
  timer->start(1);
}
rigctrl::~rigctrl(){
  delete wrapper;
}
/** No descriptions */
int rigctrl::open(s_hardware* hardware){
  azcorrection=hardware->azimuthCorrection;
  elcorrection=hardware->elevationCorrection;
  int r=0, retval=0;

  if (hardware->downlinkreceiver)
    r = wrapper->init(hardware->drig.radio, hardware->drig.port, hardware->drig.speed,
                           hardware->urig.radio, hardware->urig.port, hardware->urig.speed);
  else
    r = wrapper->init(hardware->urig.radio, hardware->urig.port, hardware->urig.speed);

	if (r) retval--;

  r=wrapper->initRotor(hardware->rotorinterface.rotor, hardware->rotorinterface.port, hardware->rotorinterface.speed, hardware->rotor450);
	if (r) retval--;
	fprintf(stderr, "Errorcode while trying to init Hardware: %i\n", retval);
	return retval;
}
/** No descriptions */
void rigctrl::setSatellite(satellite* s){
  currentSatellite=s;
}
/** No descriptions */
void rigctrl::setTransponder(transponder* t){
  rmode_t hamlibumode, hamlibdmode;
  hamlibumode=RIG_MODE_USB;
  hamlibdmode=RIG_MODE_USB;

  currentTransponder=t;
  wrapper->setPreamp(t->preamp());
  currentUplinkFreq=t->uplink();
  currentDownlinkFreq=t->downlink();
  if (t->reverse() && t->mode() == MODE_SSB) {
    hamlibumode=RIG_MODE_USB;
    hamlibdmode=RIG_MODE_LSB;
  }
  if (!t->reverse() && t->mode() == MODE_SSB) {
    hamlibumode=RIG_MODE_USB;
    hamlibdmode=RIG_MODE_USB;
  }
  if (t->mode() == MODE_FM) {
    hamlibumode=RIG_MODE_FM;
    hamlibdmode=RIG_MODE_FM;
  }
  if (t->mode() == MODE_CW) {
    hamlibumode=RIG_MODE_CW;
    hamlibdmode=RIG_MODE_CW;
  }
  setFreqs(true);
  wrapper->setModes(hamlibdmode, hamlibumode);
}
/** No descriptions */
void rigctrl::setCorrection(int corr){
  correction=corr;
}
/** gets called when a new calculation is done */
void rigctrl::slotTimeout(){
  // calculate the current satellite for accurate doppler correction!
//  if (currentSatellite) currentSatellite->propagator->calc();
  if (!currentTransponder) return;
  double freq;
  freq = wrapper->getDownlinkFrequency();
  // find out if we have a new trx frequency

  if (!wrapper->userChangedFreq()/* || !downlinkDisabled*/) {
    freq = freq + currentTransponder->downdiff();
    // remove doppler
    currentDownlinkFreq = freq - currentSatellite->doppler(freq);
  }
  setFreqs(false);
  emit (newDownlinkFreq(currentDownlinkFreq));

  if (currentTransponder->uplink())
    emit (newUplinkFreq(currentUplinkFreq+correction));
}

void rigctrl::setFreqs(bool now){
  double utrxfreq, dtrxfreq;
  // calculate a new currentuplink
  double diff = currentTransponder->downlink() - currentDownlinkFreq;
  if (currentTransponder->reverse())
    currentUplinkFreq = currentTransponder->uplink() + diff;
  else
    currentUplinkFreq = currentTransponder->uplink() - diff;
  
  // get the trx frequencies

  utrxfreq = currentUplinkFreq + correction;
  utrxfreq = utrxfreq - currentSatellite->doppler(utrxfreq);
  utrxfreq = utrxfreq - currentTransponder->updiff();

  dtrxfreq = currentDownlinkFreq + currentSatellite->doppler(currentDownlinkFreq);
  dtrxfreq = dtrxfreq - currentTransponder->downdiff();
  if (currentTransponder->uplink() == 0) utrxfreq=0;

  wrapper->setFreqs(dtrxfreq, utrxfreq, now);
  oldtrxfreq=dtrxfreq;
}
/** No descriptions */
void rigctrl::slotSetPause(bool p){
  wrapper->setPause(p);
}
/** No descriptions */
void rigctrl::setDirection(float el, float az){
  float azimuth, elevation;
  azimuth = az + azcorrection;
  elevation = el + elcorrection;

  if (elevation < 0.0) elevation = 0.0;
  if (elevation > 180.0) elevation = 180.0;

  if (azimuth >= 360.0) azimuth = azimuth - 360.0;
  if (azimuth < 0.0) azimuth = azimuth + 360.0;
  
  wrapper->setDirection(azimuth, elevation);
}
