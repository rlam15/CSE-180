# include <ros/ros.h>
# include <nav_msgs/GetPlan.h>
# include <geometry_msgs/Pose2D.h>
# include <move_base_msgs/MoveBaseAction.h>
# include <tf2_geometry_msgs/tf2_geometry_msgs.h>
# include <actionlib/client/simple_action_client.h>
# include <sensor_msgs/LaserScan.h>
# include <tf2/LinearMath/Quaternion.h>


bool moving = true;
int counter = 0;

void readSensor(const sensor_msgs::LaserScan&msg){
  int num = 0;
    for (int i = 0; i < (msg.ranges.size()-1); i++){
        if (msg.ranges[i] < 0.5)
        {
            //As we get cloer to an obstacle, we need to start incrementing
            num++;

    if(num > 5){
                moving = false;
                break;
    }
        }
    }
}

void currentPos(const move_base_msgs::MoveBaseFeedbackConstPtr& current){
  if (counter == 10){
    ROS_INFO_STREAM("Current position: (x: " << current->base_position.pose.position.x << ", y: " << current->base_position.pose.position.y << ")");
          counter = -1;
      }
      counter++;
}

void assignedGoal(){
  ROS_INFO_STREAM("Going to a random coordinate");
}

void reachedGoal(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result){
  ROS_INFO_STREAM("We reached the random coordinate");
}

int main (int c, char **v) {
  ros::init(c, v, "saferandomwalk");
  ros::NodeHandle n;
  
  move_base_msgs::MoveBaseGoal goal;
  ros::Subscriber sub = n.subscribe("/scan",1000,&readSensor);
  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> goToGoal("move_base", true);

  tf2::Quaternion qt;

  ros::Rate rate(3);

    while (ros::ok()){
      if(moving){
        
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        qt.setRPY ( 0 , 0 , ((double)(rand()%3)));

        goal.target_pose.pose.position.x = ((double)(rand()%3));
        goal.target_pose.pose.orientation = tf2::toMsg(qt);
        
        goToGoal.sendGoal(goal, &reachedGoal, &assignedGoal, &currentPos);

        ros::spinOnce();

        }else if (!moving){
          ROS_WARN("We gotta stop, we're on a crash course");
          goToGoal.cancelAllGoals();
          rate.sleep();
        }
        rate.sleep();
  }

  return 0;

}
