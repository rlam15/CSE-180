# include <cmath>
# include <ros/ros.h>
# include <geometry_msgs/Pose2D.h>
# include <move_base_msgs/MoveBaseAction.h>
# include <actionlib/client/simple_action_client.h>

float xMessage;
float yMessage;
float theta;
bool message;

void messageReceived(const geometry_msgs::Pose2D&msg) {
    xMessage = msg.x;
	yMessage = msg.y;
	theta = msg.theta;
	message = true;
}

int run(int argc, char **argv)
{
    ros::init(argc, argv, "gotoposetimeout");
    ros::NodeHandle nh;

    ros::Subscriber subPose =nh.subscribe("targetpose",1000,&messageReceived);
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
	ac("move_base",true);

    ROS_INFO_STREAM("Waiting for the server");
    while(ros::ok())
    {
        while (!ac.waitForServer()) 
        {
            exit(0);
        }
        while(!message)
        {
            ros::spinOnce();
        }
        move_base_msgs::MoveBaseGoal goal;

        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = xMessage;
        goal.target_pose.pose.position.y = yMessage;
        goal.target_pose.pose.orientation.z = sin(theta/2);
        goal.target_pose.pose.orientation.w = cos(theta/2);

        ac.sendGoal(goal);
        ac.waitForResult();
        
        ac.waitForResult(ros::Duration(5.0));
        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED && message == true) 
        {
	        ROS_INFO_STREAM("You made it!");
        }
        else 
        {
	        ROS_INFO_STREAM("You almost made it!");
            ac.cancelGoal();
        }
        //reset the message
        message = false;
    }
  return 0;
}

int main(int argc, char **argv)
{
    return run(argc, argv);
}
