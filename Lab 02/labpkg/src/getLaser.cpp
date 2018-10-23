#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void sensorReceived(const sensor_msgs::LaserScan &msg) {
	for(int  i = 0 ; i < msg.ranges.size(); i++) {
		ROS_INFO_STREAM("Data: " << msg.ranges[i]);
	}
}

int main(int argc, char **argv) {
	ros::init(argc,argv, "laserScan");
	ros::NodeHandle nh;

	ros::Subscriber laserTime = nh.subscribe("/scan",1000,&sensorReceived);

	ros::spin();	
}
