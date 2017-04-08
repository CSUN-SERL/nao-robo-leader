#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <streambuf>
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
	ros::Rate loop_rate(100);
	std_msgs::String msg;
	//string vehicle = "";
	string line = "{\"vehicle\":[    {        \"model\":\"husky\"        \"id\":\"1\"        \"battery_Percentage\":69        \"mission_Status\":\"false\"      }]";
	//string vehicle((istreambuf_iterator<char>(test_file)), istreambuf_iterator<char>());		
	cout << line << endl;
	msg.data = line;
	while(publish.getNumSubscribers() == 0){
		//std_msgs::String msg;
		//msg.data = "64.0";
		//ROS_INFO(to_string(msg.data));
		//publish.publish(msg);
		//ros::spinOnce();
		ROS_ERROR("Waiting for subscriber");
		sleep(10);
	}
	ROS_INFO("Gottem");
	publish.publish(msg);
	ros::spinOnce();
	
	return 0;
}
