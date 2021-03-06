//******************************************************************************
//  Copyright (c) 2005-2013 by Jan Van hijfte
//
//  See the included file COPYING.TXT for details about the copyright.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//******************************************************************************


#ifndef QGROUPBOX_HOOK_H
#define QGROUPBOX_HOOK_H

#include <qgroupbox.h>

#include "qwidget_hook.h"

class QGroupBox_hook : public QWidget_hook {
  Q_OBJECT
  public:
    QGroupBox_hook(QObject *handle) : QWidget_hook(handle) {
      clicked_event.func = NULL;
      clicked2_event.func = NULL;
      toggled_event.func = NULL;
    }
    void hook_clicked(QHook &hook) { 
      if ( !clicked_event.func )
        connect(handle, SIGNAL(clicked(bool)), this, SLOT(clicked_hook(bool)));
      clicked_event = hook;
      if ( !hook.func )
        disconnect(handle, SIGNAL(clicked(bool)), this, SLOT(clicked_hook(bool)));
    }
    void hook_clicked2(QHook &hook) { 
      if ( !clicked2_event.func )
        connect(handle, SIGNAL(clicked()), this, SLOT(clicked2_hook()));
      clicked2_event = hook;
      if ( !hook.func )
        disconnect(handle, SIGNAL(clicked()), this, SLOT(clicked2_hook()));
    }
    void hook_toggled(QHook &hook) { 
      if ( !toggled_event.func )
        connect(handle, SIGNAL(toggled(bool)), this, SLOT(toggled_hook(bool)));
      toggled_event = hook;
      if ( !hook.func )
        disconnect(handle, SIGNAL(toggled(bool)), this, SLOT(toggled_hook(bool)));
    }

  private slots:
    void clicked_hook(bool checked) {
      if ( clicked_event.func ) {
        typedef void (*func_type)(void *data, bool checked);
	(*(func_type)clicked_event.func)(clicked_event.data, checked);
      }
    }
    void clicked2_hook() {
      if ( clicked2_event.func ) {
        typedef void (*func_type)(void *data);
	(*(func_type)clicked2_event.func)(clicked2_event.data);
      }
    }
    void toggled_hook(bool AnonParam1) {
      if ( toggled_event.func ) {
        typedef void (*func_type)(void *data, bool AnonParam1);
	(*(func_type)toggled_event.func)(toggled_event.data, AnonParam1);
      }
    }
  private:
    QHook clicked_event;
    QHook clicked2_event;
    QHook toggled_event;
};


#endif
