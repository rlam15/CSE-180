#include <math.h>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Pose2D.h>

float xMessage;
float yMessage;
float theta;
bool message;

void messageReceived(const geometry_msgs::Pose2D &msg) {	
	xMessage = msg.x;
	yMessage = msg.y;
	theta = msg.theta;
	message = true;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "gotopose");
    ros::NodeHandle nh;

    ros::Subscriber subPose = nh.subscribe("targetpose",1000,&messageReceived);
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> 
    ac("move_base",true);

    while(ros::ok())
    {
        if (!ac.waitForServer()){
            exit(0);
        }
        while(!message){
            ros::spinOnce();
        }
        ROS_INFO_STREAM("Input taken, executing");
        move_base_msgs::MoveBaseGoal goal;

        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = xMessage;
        goal.target_pose.pose.position.y = yMessage;
        goal.target_pose.pose.orientation.z = sin(theta/2);
        goal.target_pose.pose.orientation.w = cos(theta/2);

        ac.sendGoal(goal);
        ac.waitForResult();

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        	ROS_INFO_STREAM("Thank Jesus we arrived");	
        } else {
        	ROS_INFO_STREAM("WE GOOFED SOMEWHERE");	
        }
        message = false;
    }
  return 0;
}