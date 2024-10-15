cmake_minimum_required(VERSION 3.16)
project(PA2)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Specify the build type (Debug mode)
set(CMAKE_BUILD_TYPE Debug)

# Add the executable, including all source files
add_executable(PA2 main.cpp experimentFunctions.cpp)
