cmake_minimum_required(VERSION 3.10)
project(video2ASCII)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

# This finds src/main.cpp and src/utils.cpp
file(GLOB SOURCES src/*.cpp)

add_executable(video2ASCII ${SOURCES})

# Include the utils header
target_include_directories(video2ASCII PRIVATE ${OpenCV_INCLUDE_DIRS} include)
target_link_libraries(video2ASCII PRIVATE ${OpenCV_LIBRARIES})

