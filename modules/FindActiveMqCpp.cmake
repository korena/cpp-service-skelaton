# Try to find activemq-cpp library
# Once done this will define
#  PART4_FOUND - if system found activemq-cpp library
#  ACTIVEMQCPP_INCLUDE_DIRS - The activemq-cpp include directories
#  ACTIVEMQCPP_LIBRARIES - The libraries needed to use Part4
#  ACTIVEMQCPP_DEFINITIONS - Compiler switches required for using activemq-cpp

find_path(ACTIVEMQCPP_INCLUDE_DIR
        NAMES decaf/lang/Thread.h
        PATHS ${ACTIVEMQCPP_ROOT_DIR}/include/activemq-cpp-3.9.5)
message(STATUS "ACTIVEMQCPP_ROOT_DIR: ${ACTIVEMQCPP_ROOT_DIR}")

find_library(ACTIVEMQCPP_LIBRARY NAMES libactivemq-cpp.a
        PATHS ${ACTIVEMQCPP_ROOT_DIR}/lib
        NO_DEFAULT_PATH)

message(STATUS "ACTIVEMQCPP_LIBRARY: ${ACTIVEMQCPP_LIBRARY}")

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ACTIVEMQCPP DEFAULT_MSG ACTIVEMQCPP_INCLUDE_DIR ACTIVEMQCPP_LIBRARY)

if (ACTIVEMQCPP_FOUND)
    set(ACTIVEMQCPP_LIBRARIES ${ACTIVEMQCPP_LIBRARY} )
    set(ACTIVEMQCPP_INCLUDE_DIRS ${ACTIVEMQCPP_INCLUDE_DIR} )
    set(ACTIVEMQCPP_DEFINITIONS )
else ()
    MESSAGE(STATUS "ACTIVEMQCPP NOT FOUND")
endif ()

mark_as_advanced(ACTIVEMQCPP_ROOT_DIR ACTIVEMQCPP_INCLUDE_DIR ACTIVEMQCPP_LIBRARY)
