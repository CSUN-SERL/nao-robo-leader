#include <iostream>
#include "nao_talk.hpp"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <stdio.h>
#include <string>

using namespace std;

//nao_talk.cpp allows the user to type a word, phrase, or sentence for the NAO to say
nao_talk::nao_talk()
{
    // create the published topics
    speech = node.advertise<std_msgs::String> ("/speech", 1);
    //exit() command
    exit_flag = false;
    ROS_INFO("NAO Terminal Talk Started");
    // print the exit information to the terminal
    cout << "Enter text for the NAO to speak. "
      << "To exit this node, use the 'exit()' command." << endl;
}

void nao_talk::process_command()
{
    // print out the start of the line
    cout << NAO_TERMINAL_PREFIX;
    // wait for the command
    string cmd;
    float v;
    getline(cin, cmd);
    char l[cmd.size()];
    // check if it is the exit command was used
    if (cmd.compare(EXIT_COMMAND) == 0)
        exit_flag = true;
    else
    {
        // send the text to the nao_ctrl node
        std_msgs::String msg;
        msg.data = cmd;

        speech.publish(msg);
    }
}

bool nao_talk::exit()
{
  // just return the flag
  return exit_flag;
}

int main(int argc, char **argv)
{
    // initialize ROS and the node
    ros::init(argc, argv, "nao_talk");
    sleep(2);
    // initialize the controller
    nao_talk talk;
    //nao_talk process can only be killed if the exit() command is typed into the terminal
    while (ros::ok() && !talk.exit())
    {
        talk.process_command();
        // for good practice
        ros::spinOnce();
    }
}
