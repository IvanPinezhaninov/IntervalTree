cmake_minimum_required(VERSION 2.8)

project(IntervalTree CXX)

set(INTERVALTREE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/example)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/catch)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
add_dependencies(IntervalTreeTest Catch)
