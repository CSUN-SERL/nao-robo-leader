/* 
 * File:   NaoMainWindow.h
 * Author: nwu22
 *
 * Created on November 30, 2016, 8:04 PM
 */

#ifndef _NAOMAINWINDOW_H
#define	_NAOMAINWINDOW_H

#include "ui_NaoMainWindow.h"
#include <ros/ros.h>

class NaoMainWindow : public QMainWindow {
    Q_OBJECT
public:
    NaoMainWindow();
    virtual ~NaoMainWindow();
    
public slots:
    void EnteredTxt();
    void OnUpClick();
    void OnDownClick();
    void OnRightClick();
    void OnLeftClick();
        
private:
    Ui::NaoMainWindow widget;
    ros::NodeHandle nh;
    ros::Publisher velpub;
    ros::Publisher speech;
    double linear, angular, linear_scale, angular_scale;
    void TranslateAndPublish();
};

#endif	/* _NAOMAINWINDOW_H */

