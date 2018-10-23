#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Time.h>

void timeMessageReceived(const std_msgs::Time&msg){
	ROS_INFO_STREAM("Received Time " << msg.data);
}
int main(int argc, char **argv){
        ros::init(argc,argv,"receiver");
        ros::NodeHandle nh;

	ros::Subscriber subTime = nh.subscribe("time",1000,&timeMessageReceived);

	ros::spin();
}
