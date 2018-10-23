#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <tf/transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>

using namespace std;

int main(int argc, char **argv) {
	ros::init(argc,argv,"getPose");
	ros::NodeHandle nh;

	float xDirection = 0;
	float yDirection = 0;
	float angle = 0;

	ros::Publisher pubDirection = nh.advertise<geometry_msgs::Pose2D>("targetpose",1000);

	geometry_msgs::Pose2D msg;

	ros::Rate rate(1);

	while (ros::ok()) {

		ROS_INFO_STREAM("Enter x,y, and angle");
		cin >> msg.x  >> msg.y >> msg.theta;
		pubDirection.publish(msg);
		ROS_INFO_STREAM("x direction: " << msg.x << "y direction: " << msg.y << " Angle: " << msg.theta);
		ros::Rate rate(1);		
	}
}
