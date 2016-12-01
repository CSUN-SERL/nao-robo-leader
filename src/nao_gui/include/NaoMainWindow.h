/* 
 * File:   NaoMainWindow.h
 * Author: nwu22
 *
 * Created on November 30, 2016, 8:04 PM
 */

#ifndef _NAOMAINWINDOW_H
#define	_NAOMAINWINDOW_H

#include "ui_NaoMainWindow.h"

class NaoMainWindow : public QMainWindow {
    Q_OBJECT
public:
    NaoMainWindow();
    virtual ~NaoMainWindow();
private:
    Ui::NaoMainWindow widget;
};

#endif	/* _NAOMAINWINDOW_H */

