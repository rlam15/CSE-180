
#include <ros/ros.h>
#include <std_msgs/Time.h>

int main(int argc,char ** argv){
	ros::init(argc,argv,"settime");
	ros::NodeHandle nh;

	ros::Rate rate(1);

	ros::Publisher timeTopic = nh.advertise<std_msgs::Time>("Times",1000);

	std_msgs::Time timeToSend;

	while (ros::ok()) {
	timeToSend.data = ros::Time::now();
	timeTopic.publish(timeToSend);

	rate.sleep();
	}
}
