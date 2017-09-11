cmake_minimum_required(VERSION 2.8)

project(IntervalTreeTest)

set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

include_directories(
    ${CATCH_INCLUDE_DIR}
    ${INTERVALTREE_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

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
    countinnerintervals.cpp
    countouterintervals.cpp
    countoverlappingintervals.cpp
    findinnerintervals.cpp
    findouterintervals.cpp
    findoverlappingintervals.cpp
    test.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

