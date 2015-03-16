#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <sensor_msgs/Joy.h>

geometry_msgs::Twist u_out;
geometry_msgs::Point point_out;

void joy_callback(const sensor_msgs::Joy& u_in)
{
    u_out.angular.x = u_in.axes[0];
    u_out.angular.y = u_in.axes[1];
    u_out.angular.z = u_in.axes[3];
    u_out.linear.z  = u_in.axes[4];
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"darc_manual_fly_node");
    ros::NodeHandle node;
    ros::Rate loop_rate(50);
    
    ros::Publisher u_pub;
    u_pub = node.advertise<geometry_msgs::Twist>("desired_u",1);
    
    ros::Subscriber joy_sub;
    joy_sub = node.subscribe("joy",1,joy_callback);
    
    while(ros::ok())
    {
	ros::spinOnce();
        u_pub.publish(u_out);
        loop_rate.sleep();
    }
}
