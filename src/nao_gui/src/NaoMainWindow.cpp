/*
 * File:   NaoMainWindow.cpp
 * Author: nwu22
 *
 * Created on November 30, 2016, 8:04 PM
 */

#include "NaoMainWindow.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include <std_msgs/String.h>
#include <stdlib.h>

using namespace std;

NaoMainWindow::NaoMainWindow():
        linear_scale(1), 
        angular_scale(1),
        linear(0),
        angular(0)
{
    widget.setupUi(this);
    velpub=nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    speech=nh.advertise<std_msgs::String> ("/speech", 1);
    connect(widget.upBtn, &QPushButton::pressed, 
            this, &NaoMainWindow::OnUpClick );
    connect(widget.downBtn, &QPushButton::pressed, 
            this, &NaoMainWindow::OnDownClick);
    connect(widget.rightBtn, &QPushButton::pressed, 
            this, &NaoMainWindow::OnRightClick);
    connect(widget.leftBtn, &QPushButton::pressed, 
            this, &NaoMainWindow::OnLeftClick);
    connect(widget.lineEdit, &QLineEdit::returnPressed, 
            this, &NaoMainWindow::EnteredTxt);
    connect(widget.distanceEdit, &QLineEdit::returnPressed,
            this, &NaoMainWindow::EnteredDistance);
    widget.upBtn->setAutoRepeat(true);
    widget.downBtn->setAutoRepeat(true);
    widget.rightBtn->setAutoRepeat(true);
    widget.leftBtn->setAutoRepeat(true);
}
NaoMainWindow::~NaoMainWindow() {
}

void NaoMainWindow::TranslateAndPublish()
{
    geometry_msgs::Twist vel;
    vel.angular.x=0;
    vel.angular.y=0;
    vel.angular.z=angular_scale * angular;
    vel.linear.x=linear_scale * linear;
    vel.linear.y=0;
    vel.linear.z=0;
    
    velpub.publish(vel);
    ros::spinOnce();
    angular=0;
    linear=0;
    
    
}

void NaoMainWindow::EnteredTxt()
{
    std_msgs::String msg;
    QString input;
    input=widget.lineEdit->QLineEdit::text();
    msg.data=input.toStdString();
    speech.publish(msg);
    ros::spinOnce();
}

void NaoMainWindow::OnUpClick()
{
    
    linear=1;
    this->TranslateAndPublish();
}

void NaoMainWindow::OnDownClick()
{
    linear=-1;
    this->TranslateAndPublish();
}

void NaoMainWindow::OnLeftClick()
{
    angular=1;
    this->TranslateAndPublish();
}

void NaoMainWindow::OnRightClick()
{
    angular=-1;
    this->TranslateAndPublish();
}
void NaoMainWindow::EnteredDistance()//changes distance of x value
{
    std_msgs::String msg;
    QString input;
    input=widget.distanceEdit ->QLineEdit::text();
    double meter=input.toDouble();
    linear=meter;
    
    
}




