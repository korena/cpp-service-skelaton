# CMS ( C++ messaging Service )

add_library(cms Cms.cpp HelloWorldConsumer.cpp HelloWorldProducer.cpp)

# This is not strictly required, kept here to demonstrate the use of  pkgConfig search to find external modules that are
# Cmake friendly, if you don't want it here, remove everything related to libuuid and pkg config from this file and it
# will build for you.
find_package(PkgConfig REQUIRED)
pkg_search_module(UUID REQUIRED uuid)

find_package(OpenSSL REQUIRED)
find_package(APR MODULE REQUIRED)
find_package(ActiveMqCpp MODULE REQUIRED)

if (NOT ACTIVEMQCPP_FOUND)
    message(FATAL_ERROR "Package ACTIVEMQCPP not found")
else(NOT ACTIVEMQCPP_FOUND)
    message(STATUS "Using Activemq-cpp at ${ACTIVEMQCPP_ROOT_DIR}")
endif (NOT ACTIVEMQCPP_FOUND)

if (NOT APR_FOUND)
    message(FATAL_ERROR "Package APR not found")
else (NOT APR_FOUND)
    message(STATUS "Using Apr at ${APR_ROOT_DIR}")
endif (NOT APR_FOUND)

if( OpenSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARIES})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif (OpenSSL_FOUND)

# The following is not  needed, left to demonstrate the usage of pkgConfig search to find modules
message( STATUS "Using uuid include directory: ${UUID_INCLUDE_DIRS}")
message( STATUS "Using uuid lib directory: ${UUID_LIBRARY_DIRS}")

target_include_directories(cms
        PUBLIC ${ACTIVEMQCPP_INCLUDE_DIRS}
        PUBLIC ${APR_INCLUDE_DIRS}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(cms
        ${ACTIVEMQCPP_LIBRARIES}
        ${APR_LIBRARIES}
        ${OPENSSL_LIBRARIES})
