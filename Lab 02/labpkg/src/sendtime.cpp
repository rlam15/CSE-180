#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Time.h>
int main(int argc, char **argv){
	ros::init(argc,argv,"sendtime");
	ros::NodeHandle nh;

	ros::Publisher pubTime = nh.advertise<std_msgs::Time>("time",1000);

	ros:: Rate rate(1);
	std_msgs::Time timeToSend;

	while(ros::ok()){
		timeToSend.data = ros::Time::now();
		pubTime.publish(timeToSend);
		ROS_INFO_STREAM("TIME SENT"  << timeToSend.data);
		rate.sleep();

	}
}
