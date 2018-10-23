# include <ros/ros.h>
# include <nav_msgs/GetPlan.h>
# include <geometry_msgs/Pose2D.h>
# include <tf2/LinearMath/Quaternion.h>
# include <move_base_msgs/MoveBaseAction.h>
# include <tf2_geometry_msgs/tf2_geometry_msgs.h>
# include <geometry_msgs/PoseWithCovarianceStamped.h>
# include <sensor_msgs/Imu.h>
# include <geometry_msgs/Twist.h>

double IMU;
double AMCL;

bool moving = true;

void imuF(const sensor_msgs::Imu::ConstPtr &message){
	tf2::Quaternion iq(message->orientation.x, message->orientation.y, message->orientation.z, message->orientation.w);
	IMU = iq.getAngle();
}

void amclF(const geometry_msgs::PoseWithCovarianceStampedPtr &message){
	  tf2::Quaternion aq(message->pose.pose.orientation.x, message->pose.pose.orientation.y, message->pose.pose.orientation.z,message->pose.pose.orientation.w);
	  AMCL = aq.getAngle();
}

int main(int c, char **v) {
	ros::init(c,v,"detectdivergance");
	ros::NodeHandle n;

	geometry_msgs::Twist message;
	ros::Publisher pubDir = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
	ros::Subscriber amclSub = n.subscribe("/amcl_pose",1000, amclF);
	ros::Subscriber imuSub = n.subscribe("/imu/data",1000, imuF);
    
	ros::Rate rate(5);

  	while (ros::ok() ){
		ros::spinOnce();
		// arbratary value
		if (abs(IMU - AMCL) > 0.16){
			ROS_INFO_STREAM("Divergence is coming: " << (abs(IMU-AMCL)));
			moving = false;
		} else if(!moving) {
			message.linear.x = 0;
            message.angular.z = 0;
            pubDir.publish(message);
		}
	}
 	return 0;
}