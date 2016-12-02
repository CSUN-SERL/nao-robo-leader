/*
 * File:   main.cpp
 * Author: nwu22
 *
 * Created on November 30, 2016, 7:53 PM
 */

#include <QApplication>
#include "NaoMainWindow.h"


int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    

    // create and show your widgets 
    
    ros::init(argc, argv, "NAO_GUI");
    
    NaoMainWindow m;
    m.show();
    return app.exec();
}

