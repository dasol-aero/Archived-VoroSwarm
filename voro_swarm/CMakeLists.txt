cmake_minimum_required(VERSION 3.5)
project(voro_swarm)



# ----------------------------------------------------------------------------------------------- #

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Compile Option
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# ----------------------------------------------------------------------------------------------- #



#
# Find Package
find_package(ament_cmake REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)



#
# Include
include_directories(
  include
)



# ----------------------------------------------------------------------------------------------- #

#
# Target < node_test_cal_voro_cell >
add_executable(node_test_cal_voro_cell
  src/test_cal_voro_cell/node_test_cal_voro_cell.cpp
  src/cal_voro_cell.cpp
  src/voro_cell.cpp
)
target_link_libraries(node_test_cal_voro_cell
  Eigen3::Eigen
  voro++
)
ament_target_dependencies(node_test_cal_voro_cell
  rclcpp
  geometry_msgs
  visualization_msgs
)

# ----------------------------------------------------------------------------------------------- #



#
# Install Launch Files
# install(
#   DIRECTORY launch
#   DESTINATION share/${PROJECT_NAME}
# )



#
# Install Nodes
install(TARGETS
  node_test_cal_voro_cell
  DESTINATION lib/${PROJECT_NAME}
)



#
# ament Package
ament_package()
