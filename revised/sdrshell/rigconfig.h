/***************************************************************************
                          rigconfig.h  -  description
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

#ifndef RIGCONFIG_H
#define RIGCONFIG_H

#include <qwidget.h>
#include <qstringlist.h>
#include "rigConfigBase.h"
#include "ktrack.h"

/**Configuration dialog for our hardware
  *@author Luc Langehegermann
  */

class rigConfig : public rigConfigBase  {
   Q_OBJECT
public: 
	rigConfig(QWidget *parent=0, const char *name=0,bool modal=true, WFlags fl=WDestructiveClose);
  /** sets the structure we use to store the configuration */
  void setRig(s_hardware* r);
	~rigConfig();
private:
  s_hardware* hardwareParameters;
private slots: // Private slots
  /** called, when we hit the Ok Button */
  void slotOk();
private slots: // Private slots
  /** called, when we hit the Cancel button */
  void slotCancel();
signals: // Signals
  /** No descriptions */
  void newDevices();
private: // Private methods
  /** No descriptions */
  static int addRigToList(const struct rig_caps* caps, void* data);
  static int addRotToList(const struct rot_caps* caps, void* data);
  QMap<QString, rig_model_t> rigname2rigid;
  QMap<rig_model_t, QString> rigid2rigname;
  QMap<QString, rot_model_t> rotname2rotid;
  QMap<rot_model_t, QString> rotid2rotname;
  QStringList strings;
};

#endif
