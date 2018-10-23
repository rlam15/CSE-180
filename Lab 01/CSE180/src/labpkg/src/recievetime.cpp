
#include <ros/ros.h>
#include <std_msgs/Time.h>

void timeRecieved(const std_msgs::Time&msg) {
	ROS_INFO_STREAM("Recieved Time " << msg.data);
}

int main(int argc,char ** argv) {
	ros::init(argc,argv,"recievetime");
	ros::NodeHandle nh;

	ros::Subscriber timeTopic = nh.subscribe("Time",1000, &timeRecieved);

	ros::spin();
}
