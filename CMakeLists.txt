cmake_minimum_required(VERSION 2.8)

project(IntervalTree CXX)

option(BUILD_EXAMPLE "Build example" OFF)
option(BUILD_TESTS "Build tests" OFF)

set(INTERVALTREE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "Path to IntervalTree include dir")

if(BUILD_EXAMPLE)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif(BUILD_EXAMPLE)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/catch)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
  add_dependencies(Test Catch)
endif(BUILD_TESTS)

set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/intervaltree.hpp)
add_library(${PROJECT_NAME} STATIC ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
