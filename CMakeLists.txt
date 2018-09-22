cmake_minimum_required(VERSION 3.10)
project(service)

# The version number.
set (service_VERSION_MAJOR 1)
set (service_VERSION_MINOR 0)
set (service_VERSION_INCREMENT 0)


# should we use our own math functions?
option (USE_MYMATH
        "Use service provided math implementation" ON)

set(CMAKE_CXX_STANDARD 14)

add_executable( service Main.cpp)

#[=[
     Configure a header file to pass some of the CMake settings
     to the source code.
#]=]
configure_file (
        "${PROJECT_SOURCE_DIR}/include/ServiceConfig.h.in"
        "${PROJECT_BINARY_DIR}/ServiceConfig.h"
)

#[=[
 Add the binary tree to the search path for include files
 so that we will find TutorialConfig.h
#]=]
target_include_directories( service PRIVATE "${PROJECT_BINARY_DIR}")


# external (third party)
# Apr
add_subdirectory(third_party/Apr)
# Apr-util
add_subdirectory(third_party/Apr-util)
# Activemq-cpp
add_subdirectory(third_party/Activemq_cpp)
#gRPC
#add_subdirectory(third_party/gRPC)


add_subdirectory(src/cms)
# add the MathFunctions library?
#
if (USE_MYMATH)
    add_subdirectory(src/math_functions)
    set (OPT_LIBS ${OPT_LIBS} mathFunctions)
endif (USE_MYMATH)


# The OPT_LIBS will expose their include dirs, so they can be included in Main.cpp (as long as they're public),
# so we don't need to specify the include directories explicitly here
target_link_libraries( service ${OPT_LIBS} cms)


# add the install targets
install (TARGETS service DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/ServiceConfig.h"
        DESTINATION include)


# basic preliminary tests for executable after install

include(CTest)

# does the application run
add_test (ServiceRuns service 25)
# does it sqrt of 25
add_test (ServiceComputes25 service 25)
set_tests_properties (ServiceComputes25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
# does it handle negative numbers
add_test (ServiceNegative service -25)
set_tests_properties (ServiceNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")
# does it handle small numbers
add_test (ServiceSmall service 0.0001)
set_tests_properties (ServiceSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
# does the usage message work?
add_test (ServiceUsage service)
set_tests_properties (ServiceUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")