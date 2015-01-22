#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Point.h>
#include <iostream>

geometry_msgs::Vector3 u_out;
geometry_msgs::Point point_out;

void u_callback(const geometry_msgs::Vector3& u_in)
{
    u_out.x = u_in.x;
    u_out.y = u_in.y;
    u_out.z = u_in.z;
}

void point_callback(const geometry_msgs::Vector3& u_in)
{
    point_out.x = u_in.x;
    point_out.y = u_in.y;
    point_out.z = u_in.z;
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"darc_manual_fly_node");
    ros::NodeHandle node;
    ros::Rate loop_rate(50);
    
    ros::Publisher u_pub;
    u_pub = node.advertise<geometry_msgs::Vector3>("new_u",1);
    
    ros::Publisher point_pub;
    point_pub=node.advertise<geometry_msgs::Point>("/vrep/input",1);
    
    ros::Subscriber u_sub;
    u_sub = node.subscribe("desired_u",1,u_callback);
    
    ros::Subscriber point_sub;
    point_sub = node.subscribe("desired_u",1,point_callback);
    
    std::cout << std::endl << std::endl << "Stuff" << std::endl << std::endl;
    while(ros::ok())
    {
        u_pub.publish(u_out);
        point_pub.publish(point_out);
        ros::spinOnce();
        loop_rate.sleep();
    }
}
