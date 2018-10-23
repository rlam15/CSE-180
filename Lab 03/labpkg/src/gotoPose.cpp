#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf/tfMessage.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>


float xDirection = 0;
float yDirection = 0;
float angle = 0;
float xDesired = 0;
float yDesired = 0;
float angleDesired = 0;

using namespace std;

// Changes from 2D to T
void directionsReceived(const geometry_msgs::Pose2D&msg) {
	xDirection = msg.x;
	yDirection = msg.y;
	angle = msg.theta;	
}

 void location(const tf::tfMessage&msg) {
 	
}

int main(int argc, char **argv) {

	ros::init(argc,argv,"gotoPose");
	ros::NodeHandle nh;

	ros::Subscriber subDirections = nh.subscribe("targetpose",1000,&directionsReceived);
	ros::Subscriber subTF = nh.subscribe("/tf",1000,&location);
	ros::Publisher pubDirection = nh.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel",1000);

	ros::Rate rate(3);

	tf2_ros::Buffer buffer;
	tf2_ros::TransformListener listener(buffer);

	geometry_msgs::TransformStamped transformstamped;

	while (nh.ok()) {

		// msg.linear.x = xDirection;
		// msg.linear.y = yDirection;
		// msg.angular.z = angle;
		// pubDirection.publish(msg);
		// ROS_INFO_STREAM("Sent Data x:" << msg.linear.x << "Sent data y:" <<msg.linear.y << "Sent data z: " << msg.angular.z);  

		ros::spinOnce();
		try {
			transformstamped = buffer.lookupTransform("base_link","odom",ros::Time(0));
		} catch(tf2::TransformException &exception) {
			ROS_WARN("%s",exception.what());
			ros::Duration(1.0).sleep();
			continue;
		}
		geometry_msgs::Twist msg;
		msg.angular.y = 4.0 * atan2(transformstamped.transform.translation.y, transformstamped.transform.translation.x);
		msg.linear.x = 0.5 * sqrt(pow(transformstamped.transform.translation.x,2) + pow(transformstamped.transform.translation.y,2));
		pubDirection.publish(msg);
		ROS_INFO_STREAM("Transformation::" << transformstamped);
		rate.sleep();
		
	}
	return 0;

}
