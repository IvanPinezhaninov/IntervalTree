cmake_minimum_required(VERSION 2.8.11)

project(IntervalTree CXX)

option(BUILD_EXAMPLE "Build example" OFF)
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_EXAMPLE)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif(BUILD_EXAMPLE)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/catch)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(BUILD_TESTS)

set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/intervaltree.hpp)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(FILES ${HEADERS} DESTINATION include)
