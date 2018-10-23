cmake_minimum_required(VERSION 2.8.3)
project(labpkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
  tf2_geometry_msgs
  tf2_ros
  tf2
  tf
  map_server
  amcl
  move_base
)

catkin_package()
include_directories( ${catkin_INCLUDE_DIRS})
add_executable(sendtime src/sendtime.cpp)
add_executable(receivetime src/receivetime.cpp)
add_executable(moveBot src/moveBot.cpp)
add_executable(getLaser src/getLaser.cpp)
add_executable(getPose src/getPose.cpp)
add_executable(gotoPose src/gotoPose.cpp)
add_executable(gotoposetimeout src/gotoposetimeout.cpp)


target_link_libraries(sendtime ${catkin_LIBRARIES})
target_link_libraries(receivetime ${catkin_LIBRARIES})
target_link_libraries(moveBot ${catkin_LIBRARIES})
target_link_libraries(getLaser ${catkin_LIBRARIES})
target_link_libraries(getPose ${catkin_LIBRARIES})
target_link_libraries(gotoPose ${catkin_LIBRARIES})
target_link_libraries(gotoposetimeout ${catkin_LIBRARIES})