cmake_minimum_required(VERSION 2.8.3)
project(random)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
  tf2_geometry_msgs
  tf2_ros
  tf2
  tf
)

catkin_package()
include_directories( ${catkin_INCLUDE_DIRS})

add_executable(listener src/listener.cpp)
add_executable(repeat src/repeat.cpp)

target_link_libraries(listener ${catkin_LIBRARIES})
target_link_libraries(repeat ${catkin_LIBRARIES})
