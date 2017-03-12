#include <iostream>
#include "nao_talk.hpp"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <naoqi_bridge_msgs/WordRecognized.h>
#include <stdio.h>
#include <string>

using namespace std;

class nao_speech_response{
    public:
        nao_speech_response();
        void respond();
        
    private:
        ros::NodeHandle nh;
        ros::Publisher wordRecPub;
        //The string array that holds all the vocab, currently its constructed
        //in a way that allows you to keep adding but might have problems if there are n+ amount of words
        //same with confidence(its just an array of confidence values
        vector<string> vocab;
        vector<float> confidence;                             
};

//Constructor
nao_speech_response::nao_speech_response(){
    /*
    since the topic word_recognized publishes to naoqi_bridge_msgs that is the type
    that gets put when advertising the node, then just the type you are accessing in
    this case WordRecognized.
    */
    wordRecPub = nh.advertise<naoqi_bridge_msgs::WordRecognized>("/word_recognized", 1);
    cout << "Enter vocabulary that the NAO RoboLeader will have in its WordRecognized list"
        << endl;
}

void nao_speech_response::respond(){
    string input;
    //Get user input from terminal to add to /word_recognized vector
    getline(cin, input);
    //Makes sure it isn't empty; haven't tried to make it null value
    if(input != ""){
        //Created a WordRecognized from naoqi_bridge_msgs to access its values
        //If confused refer back to my teleop and talk classes where I essentially do the same thing
        naoqi_bridge_msgs::WordRecognized word;
        //added the word and confidence value, respectively, to the vector
        vocab.push_back(input);
        confidence.push_back(100);
        //Changing the vocabulary of the robot by setting it equal to my vectors
        word.words = vocab;
        word.confidence_values = confidence;
        //I publish to word_Recognized with word as a parameter (again refer to my other classes if confused)
        wordRecPub.publish(word);
    }
    else
        cout << "Enter a word at least 1 letter long" << endl;
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nao_speech_response");
    nao_speech_response response;
    while(ros::ok()){
        response.respond();
        ros::spinOnce();
    }
}
