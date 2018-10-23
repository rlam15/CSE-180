#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Eigenvalues>
#include <cmath>
#include <iostream>

using namespace std;

double c1, c2, c3;
double goal = 0.975;
double pi = M_PI;
double volume;
Eigen::MatrixXd matrix(3,3);


void EKF(const nav_msgs::Odometry&msg){
	
	matrix(0,0) = msg.pose.covariance[14];
	matrix(0,1) = msg.pose.covariance[15];
	matrix(0,2) = msg.pose.covariance[16];
	matrix(1,0) = msg.pose.covariance[20];
	matrix(1,1) = msg.pose.covariance[21];
	matrix(1,2) = msg.pose.covariance[22];
	matrix(2,0) = msg.pose.covariance[26];
	matrix(2,1) = msg.pose.covariance[27];
	matrix(2,2) = msg.pose.covariance[28];
	//Eign Solver
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(matrix);
	//getting the eigen values for each column...x, y, z
	c1 = solver.eigenvalues().x();
	c2 = solver.eigenvalues().y();
	c3 = solver.eigenvalues().z();

	double r1 = goal * sqrt(c1);
	double r2 = goal * sqrt(c2);
	double r3 = goal * sqrt(c3);

	volume = (4/3)*pi*r1*r2*r3;
}
int main (int c, char **v) {

	ros::init(c,v, "uncertainty");
	ros::NodeHandle nh;
	ros::Subscriber ekf = nh.subscribe("/odometry/filtered",10, &EKF);
	ros::Rate r(1);

  	while (ros::ok() ) {
        ros::spinOnce();
		r.sleep();

		cout << endl;
        ROS_INFO_STREAM("The volume is " << volume);
		ROS_INFO_STREAM("Pose Covariance Matrix: ");
		ROS_INFO_STREAM(matrix(0,0)<<"\t"<<matrix(0,1)<<"\t"<<matrix(0,2));
		ROS_INFO_STREAM(matrix(1,0)<<"\t"<<matrix(1,1)<<"\t"<<matrix(1,2));
		ROS_INFO_STREAM(matrix(2,0)<<"\t"<<matrix(2,1)<<"\t"<<matrix(2,2));
		ROS_INFO_STREAM("Eigen Value 1:\t"<<c1);
		ROS_INFO_STREAM("Eigen Value 2:\t"<<c2);
		ROS_INFO_STREAM("Eigen Value 3:\t"<<c3);
		cout << endl;

	}
 	return 0;


}
