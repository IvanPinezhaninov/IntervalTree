#============================================================================
#
# Copyright (C) 2019 Ivan Pinezhaninov <ivan.pinezhaninov@gmail.com>
#
# This file is part of the IntervalTree - Red-Black balanced interval tree
# which can be found at https://github.com/IvanPinezhaninov/IntervalTree/.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
# THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#============================================================================

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

add_dependencies(${PROJECT_NAME} ${EXTERNAL_PROJECT_NAME})
