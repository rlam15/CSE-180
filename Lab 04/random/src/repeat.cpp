#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf/tfMessage.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using namespace std;

float xRecieved = 0;
float yRecieved = 0;
float zRecieved = 0;

void msgReceived(const geometry_msgs::Twist &msg) {
	xRecieved = msg.linear.x;
	yRecieved = msg.linear.y;
	zRecieved = msg.angular.z;
	// ROS_INFO_STREAM("Test Coordinates::" << xRecieved << yRecieved << zRecieved);
}

int main (int argc, char **argv) {

	float tempX = 0;
	float tempY = 0;
	float tempZ = 0;
	int count = 1;

	ros::init(argc,argv,"repeat");
	ros::NodeHandle nh;

	//Take b's movements and call function msgReceived
	//Store the movements into xRecieved and so on.
	ros::Subscriber subDir = nh.subscribe("husky_beta/husky_velocity_controller/cmd_vel", 1000, &msgReceived);
	ros::Publisher pubDir = nh.advertise<geometry_msgs::Twist>("husky_alpha/husky_velocity_controller/cmd_vel",1000);	

	
	geometry_msgs::Twist msg;
	
	// Repeat b's movement
	while (ros::ok()) {
		ros::Rate rate(2);
		ros::spinOnce();
		
		ROS_INFO_STREAM("Transformation: " << count << " of Beta Bot (x,y,z): " << xRecieved << " " << yRecieved << " " << zRecieved);
		
		if (count % 2 == 1) {
			tempX = xRecieved;
			tempY = yRecieved;
			tempZ = zRecieved;

		}

		if (count % 2 == 0) {
			msg.linear.x = (tempX - xRecieved);
			msg.linear.y = (tempY - yRecieved);
			msg.angular.z = (tempZ - zRecieved);

		ROS_INFO_STREAM("Final transformation of Alpha Bot (x,y,z): " << msg.linear.x << " " << msg.linear.y << " " << msg.angular.z << endl);
		pubDir.publish(msg);
			
		}
		
		rate.sleep();
		count++;

		
	}
	ROS_INFO_STREAM("Took two commands, ending program");
}