#ifndef NAO_TALK_H_
#define NAO_TALK_H_
#include <ros/ros.h>

#define NAO_TERMINAL_PREFIX "> "
#define EXIT_COMMAND "exit()"
#define VOLUME_COMMAND "volume(%f)"
#define LANG_COMMAND "lang(%s)"

//nao_talk header file
class nao_talk
{
    public:
        /* Creates a nao_talk.
        
         Creates a nao_talk object that can be used control of the NAO's text-to-speech module with ROS.
        */
        nao_talk();
        /*
       	* \brief Process a line of input from terminal.
        * If an exit() command is printed, then the node is closed.
        */
        void process_command();
        /*
		If this exit() is called in terminal then it will kill the process
	*/
        bool exit();

    private:
        ros::NodeHandle node; //a ROS NodeHandle
        ros::Publisher speech; //the nao_say topics
        bool exit_flag; // used to check if the user used the 'exit' command
};

#endif
