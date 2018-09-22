# CMS ( C++ messaging Service )

add_library(cms Cms.cpp)

find_package(OpenSSL REQUIRED)

if( OpenSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARIES})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif (OpenSSL_FOUND)


# This is so I won't have to use find_package and all that crap
add_dependencies(cms Apr)
# Apr
get_target_property(Apr_INCLUDE_DIRS Apr Apr_INCLUDE_DIRS)
get_target_property(Apr_LIBRARIES Apr Apr_LIBRARIES)

target_include_directories(cms
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${Apr_INCLUDE_DIRS})

target_link_libraries(cms ${Apr_LIBRARIES} ${OPENSSL_LIBRARIES})
