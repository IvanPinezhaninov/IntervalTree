cmake_minimum_required(VERSION 2.8.11)

project(Test CXX)

add_definitions(-std=c++11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

set(HEADERS
  utils/common.h
  utils/intervals.h
  utils/timer.h
  utils/random.h
)

set(SOURCES
  utils/intervals.cpp
  utils/timer.cpp
  utils/random.cpp
  benchmark.cpp
  constructors.cpp
  countinnerintervals.cpp
  countintervalscontainpoint.cpp
  countouterintervals.cpp
  countoverlappingintervals.cpp
  findinnerintervals.cpp
  findintervalscontainpoint.cpp
  findouterintervals.cpp
  findoverlappingintervals.cpp
  test.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} IntervalTree Catch)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
