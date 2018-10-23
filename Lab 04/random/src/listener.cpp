#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf/tfMessage.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int agrc, char **argv) {
	ros::init(agrc,argv,"listener");
	ros::NodeHandle nh;

	tf2_ros::Buffer buffer;
	tf2_ros::TransformListener listener(buffer);

	geometry_msgs::TransformStamped transformstamped;

	while (ros::ok()) {
		ros::spinOnce();
		try {
			transformstamped = buffer.lookupTransform("husky_beta/base_link","husky_alpha/base_link",ros::Time(0));
		} catch(tf2::TransformException &exception) {
			ROS_WARN("%s",exception.what());
			ros::Duration(1.0).sleep();
			continue;
		}
		ROS_INFO_STREAM("Transformation:: " << transformstamped);
	}
	return 0;

}