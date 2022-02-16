cmake_minimum_required(VERSION 3.10.0)

# Project name and version
project(neuvisys-simulator
        VERSION 1.0.0
        LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

find_package(OpenCV 4.0.0 REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs cv_bridge)

include_directories ("/usr/include/opencv4/")
include_directories(${catkin_INCLUDE_DIRS})

set(PROJECT_SOURCES
        src/SimulationInterface.cpp
        src/Motor.cpp
        src/FrameToEvents.cpp
        src/Utils.cpp)

add_executable(neuvisys-simulator src/mainSimulator.cpp ${PROJECT_SOURCES})
target_link_libraries(neuvisys-simulator ${catkin_LIBRARIES} ${OpenCV_LIBS})
