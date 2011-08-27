/***************************************************************************
                          rigconfig.cpp  -  description
                             -------------------
    begin                : Sun May 5 2002
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

#include "rigconfig.h"
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <stdio.h>

rigConfig::rigConfig(QWidget *parent, const char *name, bool modal, WFlags fl) : rigConfigBase(parent,name,modal,fl) {
  QObject::connect(buttonOk, SIGNAL(clicked()), this, SLOT(slotOk()));
  QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(slotCancel()));
  QObject::connect(downlinkCheckBox, SIGNAL(toggled(bool)), downlinkGroupBox, SLOT(setEnabled(bool)));
}

/** No descriptions */
int rigConfig::addRigToList(const struct rig_caps* caps, void* data){
	QString name;
  rigConfig* r = (rigConfig*)data;
	name=caps->model_name;
	if (name == "Dummy")
		name = "None";
  r->rigname2rigid[name] = caps->rig_model;
  r->rigid2rigname[caps->rig_model] = name;
 	r->strings << name;
  return -1; // not 0 --> we want all rigs
}

int rigConfig::addRotToList(const struct rot_caps* caps, void* data) {
	QString name;
  rigConfig* r = (rigConfig*)data;
	name = caps->model_name;
	if (name == "Dummy")
		name = "None";
  r->rotname2rotid[name] = caps->rot_model;
  r->rotid2rotname[caps->rot_model] = name;
  r->strings << name;
  return -1;
}

rigConfig::~rigConfig(){
}
/** sets the structure we use to store the configuration */
void rigConfig::setRig(s_hardware* r)
{
  hardwareParameters=r;
  bool found;
  found=false;

  // fill the rotor interface boxes

  rot_load_all_backends();
//  rotorInterface->insertItem("none");
  rot_list_foreach(addRotToList, this);
  strings.sort();
  rotorInterface->insertStringList(strings);
  strings.clear();
    
//  rotname2rotid["none"] = ROT_MODEL_DUMMY;
//  rotid2rotname[ROT_MODEL_DUMMY] = "none";

  rotorInterface->setCurrentText(rotid2rotname[hardwareParameters->rotorinterface.rotor]);
  rotorPort->setCurrentText(hardwareParameters->rotorinterface.port);
  rotorSpeed->setCurrentText(QString::number(hardwareParameters->rotorinterface.speed));
  
  found=false;

  azimuthCorrectionEdit->setText(QString::number(hardwareParameters->azimuthCorrection, 'f', 1));
  elevationCorrectionEdit->setText(QString::number(hardwareParameters->elevationCorrection, 'f', 1));

  // fill the rig combo boxes

  rig_load_all_backends();
//  utrxEdit->insertItem("none");
//  dtrxEdit->insertItem("none");
  rig_list_foreach(addRigToList, this);
  strings.sort();
  utrxEdit->insertStringList(strings);
  dtrxEdit->insertStringList(strings);
  strings.clear();
  
//  rigname2rigid["none"] = RIG_MODEL_DUMMY;
//  rigid2rigname[RIG_MODEL_DUMMY] = "none";

  utrxEdit->setCurrentText(rigid2rigname[hardwareParameters->urig.radio]);
  dtrxEdit->setCurrentText(rigid2rigname[hardwareParameters->drig.radio]);

  downlinkCheckBox->setChecked(hardwareParameters->downlinkreceiver);

  uportEdit->setCurrentText(hardwareParameters->urig.port);
  dportEdit->setCurrentText(hardwareParameters->drig.port);

  uspeedEdit->setCurrentText(QString::number(hardwareParameters->urig.speed));
  dspeedEdit->setCurrentText(QString::number(hardwareParameters->drig.speed));

  rotorCheckBox->setChecked(hardwareParameters->rotor450);
}
/** called, when we hit the Cancel button */
void rigConfig::slotCancel(){
  reject();
}
/** called, when we hit the Ok Button */
void rigConfig::slotOk(){
//  hardwareParameters->fodtrackDevice=fodtrackPort->currentText();

  hardwareParameters->rotorinterface.port=rotorPort->currentText();
  hardwareParameters->rotorinterface.speed=rotorSpeed->currentText().toInt();
  hardwareParameters->rotorinterface.rotor=rotname2rotid[rotorInterface->currentText()];

  hardwareParameters->drig.port=dportEdit->currentText();
  hardwareParameters->drig.radio=rigname2rigid[dtrxEdit->currentText()];
  hardwareParameters->drig.speed=dspeedEdit->currentText().toInt();

  hardwareParameters->urig.port=uportEdit->currentText();
  hardwareParameters->urig.radio=rigname2rigid[utrxEdit->currentText()];
  hardwareParameters->urig.speed=uspeedEdit->currentText().toInt();

  hardwareParameters->downlinkreceiver=downlinkCheckBox->isChecked();

  hardwareParameters->rotor450=rotorCheckBox->isChecked();

  hardwareParameters->azimuthCorrection=azimuthCorrectionEdit->text().toDouble();
  hardwareParameters->elevationCorrection=elevationCorrectionEdit->text().toDouble();

  emit (newDevices());
  accept();
}
