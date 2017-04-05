#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char** argv){
	ros::init(argc, argv, "nao_events_publisher");
	ros::NodeHandle nh;
	ros::Publisher publish = nh.advertise<std_msgs::String>("vehicleEvent", 1000);
	ros::Rate loop_rate(.5);
	while(ros::ok()){
		std_msgs::String msg;
		msg.data = "Mission Complete, Bitch!";
		ROS_INFO("%s", msg.data.c_str());
		publish.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
