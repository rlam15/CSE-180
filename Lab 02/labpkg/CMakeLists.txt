cmake_minimum_required(VERSION 2.8.3)
project(labpkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
)

catkin_package()
include_directories( ${catkin_INCLUDE_DIRS})
add_executable(sendtime src/sendtime.cpp)
add_executable(receivetime src/receivetime.cpp)
add_executable(moveBot src/moveBot.cpp)
add_executable(getLaser src/getLaser.cpp)

target_link_libraries(sendtime ${catkin_LIBRARIES})
target_link_libraries(receivetime ${catkin_LIBRARIES})
target_link_libraries(moveBot ${catkin_LIBRARIES})
target_link_libraries(getLaser ${catkin_LIBRARIES})
