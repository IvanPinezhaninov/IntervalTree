cmake_minimum_required(VERSION 2.8)

project(IntervalTreeExample CXX)

set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

include_directories(${INTERVALTREE_INCLUDE_DIR})

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
