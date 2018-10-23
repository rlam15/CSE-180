cmake_minimum_required(VERSION 2.8.3)
project(final)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  amcl
  move_base
  sensor_msgs
  geometry_msgs
  map_server
  tf2
  tf2_ros
)
find_package(cmake_modules REQUIRED)
find_package(Eigen REQUIRED)
catkin_package()
include_directories(
  ${catkin_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS}
)
add_executable(uncertainty src/uncertainty.cpp)
add_executable(map_reader src/map_reader.cpp)

target_link_libraries(uncertainty ${catkin_LIBRARIES})
target_link_libraries(map_reader ${catkin_LIBRARIES})

