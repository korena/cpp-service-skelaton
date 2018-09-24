# CMS ( C++ messaging Service )

add_library(cms Cms.cpp HelloWorldConsumer.cpp HelloWorldProducer.cpp)

find_package(OpenSSL REQUIRED)
find_package(APR MODULE REQUIRED)
find_package(ACTIVEMQCPP MODULE REQUIRED)

if (NOT ACTIVEMQCPP_FOUND)
    message(FATAL_ERROR "Package ACTIVEMQCPP not found")
endif (NOT ACTIVEMQCPP_FOUND)

if (NOT APR_FOUND)
    message(FATAL_ERROR "Package APR not found")
endif (NOT APR_FOUND)

if( OpenSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARIES})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif (OpenSSL_FOUND)

target_include_directories(cms
        PUBLIC ${ACTIVEMQCPP_INCLUDE_DIRS}
        PUBLIC ${APR_INCLUDE_DIRS}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(cms
        ${ACTIVEMQCPP_LIBRARIES}
        ${APR_LIBRARIES}
        ${OPENSSL_LIBRARIES})
