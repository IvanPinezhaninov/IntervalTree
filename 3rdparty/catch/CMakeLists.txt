cmake_minimum_required(VERSION 2.8.11)

project(Catch CXX)

include(ExternalProject)
find_package(Git REQUIRED)

set(EXTERNAL_PROJECT_NAME CatchProject)

ExternalProject_Add(
    ${EXTERNAL_PROJECT_NAME}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v2.2.3
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(${EXTERNAL_PROJECT_NAME} SOURCE_DIR)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${SOURCE_DIR}/single_include)
