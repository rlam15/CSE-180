#include <ros/ros.h>
//Might be wrong
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
// #include <map_server> 

//might need scaope map_server
void loadMapFromFile(const nav_msgs::MapMetaData &msg) {
	ROS_INFO_STREAM(msg);
}

//-1 is uknown, 0 is known, 100 has an object
void decipherMap(const nav_msgs::OccupancyGrid & msg) {

}

int main(int c, char ** v) {
	ros::init(c,v,"map_reader");
	ros::NodeHandle nh;
	ros::Subscriber map = nh.subscribe("/map_metadata", 1000, &loadMapFromFile);
	// Map_Server::Map_Server

	ros::spin();
}