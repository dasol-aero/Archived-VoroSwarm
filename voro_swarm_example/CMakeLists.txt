cmake_minimum_required(VERSION 3.5)
project(voro_swarm_example)



# Dependency ---------------------- #
#
# $ sudo apt-get install voro++-dev
#
# --------------------------------- #



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
find_package(Eigen3 3.3 REQUIRED NO_MODULE)



#
# Include
include_directories(
  include
)



# ----------------------------------------------------------------------------------------------- #

add_executable(voro_swarm_example
  src/voro_swarm_example.cpp
)
target_link_libraries(voro_swarm_example
  Eigen3::Eigen
  voro++
)

# ----------------------------------------------------------------------------------------------- #
