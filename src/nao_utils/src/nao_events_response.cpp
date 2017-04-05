#include <iostream>
#include "nao_talk.hpp"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <stdio.h>
#include <string>

using namespace std;

class nao_events_response{
	public:
		nao_events_response(){
			speech = nodeH.advertise<std_msgs::String>("/speech", 1);
			get_event = nodeH.subscribe("vehicleEvent", 1, &nao_events_response::process_event, this);		
		}
		void process_event(const std_msgs::String::ConstPtr& msg){
			ROS_INFO("I heard [%s]", msg->data.c_str());
			std_msgs::String mes;
			mes.data = msg->data.c_str();
			speech.publish(mes);
		}
	private:
		ros::NodeHandle nodeH;
		ros::Publisher speech;
		ros::Subscriber get_event;

	/*
		nao responds given a unique event
		for instance,
		husky sends GCS battery life, GCS sends
		info to nao and nao gives response based on event	
	*/
};	

	int main(int argc, char** argv){
		ros::init(argc, argv, "nao_events_response");
		nao_events_response nao_events_response;
		ros::spin();
		return 0;
	}
