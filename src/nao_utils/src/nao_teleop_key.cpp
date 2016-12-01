#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
//Right, Left, Up, Down
#define KEYCODE_R 0X43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71

class TeleopNao{
    //essentially the header or what initializes the TeleopNao object
    public:
        TeleopNao();
        void keyLoop();
        
    private:
        ros::NodeHandle nh;
        double linear, angular, l, a;
        ros::Publisher velpub;
};

TeleopNao::TeleopNao():
    //initializing the linear and angular values
    linear(0),
    angular(0),
    l(1.0),
    a(1.0)
    {
        nh.param("scale_angular", a, a);
        nh.param("scale_linear", l, l);
        
        velpub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    }
    
int kfd = 0;
struct termios cooked, raw;
//allows the process to end with ctrl+c
void quit(int sig){
    tcsetattr(kfd, TCSANOW, &cooked);
    ros::shutdown();
    exit(0);
}
//the main that creates the object and uses the keyloop
int main(int argc, char** argv){
    ros::init(argc, argv, "teleop_nao");
    TeleopNao teleop_nao;
    
    signal(SIGINT, quit);
    teleop_nao.keyLoop();
    
    return 0;
}
//this allows the user to control the NAO's movement with the left, right, up down, arrow keys
void TeleopNao::keyLoop(){
    char c;
    bool pressed = false;
    
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    //New Line
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
    
    puts("Reading from keyboard");
    puts("--------------------------");
    puts("Use arrow keys to move the nao.");
    
    for(;;){
        if(read(kfd, &c, 1) < 0){
            perror("read():");
            exit(-1);
        }
        
        linear = angular = 0;
        ROS_DEBUG("value: 0x%02X\n", c);
        
        switch(c){
            case KEYCODE_L:
                ROS_DEBUG("LEFT");
                angular = 1.0;
                pressed = true; break;
            case KEYCODE_R:
                ROS_DEBUG("RIGHT");
                angular = -1.0;
                pressed = true; break;
            case KEYCODE_U:
                ROS_DEBUG("UP");
                linear = 1.0;
                pressed = true; break;
            case KEYCODE_D:
                ROS_DEBUG("DOWN");
                linear = -1.0;
                pressed = true; break;
        }
        
        geometry_msgs::Twist vel;
        vel.angular.x = 0;
        vel.angular.y = 0;
        vel.angular.z = a*angular;
        vel.linear.x = l*linear;
        vel.linear.y = 0;
        vel.linear.z = 0;
        if(pressed == true){
            velpub.publish(vel);
            pressed = false;
            ros::spinOnce();
        }
    }
    
    return;
}
