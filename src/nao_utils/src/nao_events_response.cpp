#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "nao_talk.hpp"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
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
			//ostringstream ss;
			//ss << msg->data;
			//string battery(ss.str());
			ROS_INFO("I heard [%s]", msg->data.c_str());
			string battery = msg->data.c_str();
			int index = battery.find("battery_Percentage") + 20;
			string str2 = battery.substr(index-20);
			int index2 = str2.find(" ");
			cout << str2.substr(0, index2) << endl;
			std_msgs::String mes;
			mes.data = "Husky have " + msg->data + "% battery life left";
			speech.publish(mes);
		}
	private:
		ros::NodeHandle nodeH;
		ros::Publisher speech;
		ros::Subscriber get_event;

	/*
		nao responds given a unique event
		for instance,
		husky sends battery life, to nao and nao gives response based on event	
	*/
};	

	int main(int argc, char** argv){
		ros::init(argc, argv, "nao_events_response");
		nao_events_response nao_events_response;
		ros::spin();
		return 0;
	}
