#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main (int argc, char **argv) {

	ros::init(argc,argv, "moveBot");
	ros::NodeHandle nh;

	ros::Publisher pubDirection = nh.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel",1000);
	
	ros:: Rate rate(10);
	int lengthTraveled = 0;
	int timesTurned = 0;
	int side = 0;

	while(ros::ok()){
		geometry_msgs::Twist msg;

		if(lengthTraveled < 20) {
			msg.linear.x = 20;
			lengthTraveled++;
		} else if (timesTurned < 4) {
			msg.linear.x = 0;
			msg.angular.z = 10;
			timesTurned++;
		} else if (side <= 5) {
			side++;
			lengthTraveled = 0;
			timesTurned = 0;
		}
		pubDirection.publish(msg);
		rate.sleep();
	}
}
