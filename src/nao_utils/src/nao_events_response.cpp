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
			get_event = nodeH.subscribe("vehicle_events", 1, &nao_events_response::process_event, this);		
		}
		void process_event(const std_msgs::String::ConstPtr& msg){
			//ostringstream ss;
			//ss << msg->data;
			//string battery(ss.str());
			ROS_INFO("I heard [%s]", msg->data.c_str());
			string battery = msg->data.c_str();
			int index = battery.find("battery_Percentage");
			int index2 = battery.find("mission_Status");			
			//string str2 = battery.substr(index-20);
			//int index2 = str2.find(" ");
			//cout << index << endl;
			//cout << battery.substr(index, 18) << endl;
			string battery_percentage = battery.substr(index+20, 4);
			string mission = battery.substr(index2+16, 1);
			string mission_status = "";
			
			if(mission == "0"){
				mission_status = "Mission status incomplete";
			}else{
				mission_status = "Mission status complete";
			}
			//cout << mission << "its works" << endl;
			std_msgs::String mes;
			mes.data = "Husky is at " + battery_percentage + "% battery. " + " " + mission_status;
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
