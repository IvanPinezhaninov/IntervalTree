cmake_minimum_required(VERSION 2.8)

project(CatchBuilder CXX)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    Catch
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(Catch SOURCE_DIR)
set(CATCH_INCLUDE_DIR ${SOURCE_DIR}/single_include CACHE INTERNAL "Path to Catch include dir")
