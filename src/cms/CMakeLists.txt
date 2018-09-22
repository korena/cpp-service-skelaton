# CMS ( C++ messaging Service )

add_library(cms Cms.cpp HelloWorldConsumer.cpp HelloWorldProducer.cpp)

# This is so I won't have to use find_package and all that crap
add_dependencies(cms Activemq-cpp)

#Apr
get_target_property(Apr_INCLUDE_DIRS Apr Apr_INCLUDE_DIRS)
get_target_property(Apr_LIBRARIES Apr Apr_LIBRARIES)
#Apr-util
get_target_property(Apr-util_INCLUDE_DIRS Apr-util Apr-util_INCLUDE_DIRS)
get_target_property(Apr-util_LIBRARIES Apr-util Apr-util_LIBRARIES)
# Activemq-cpp
get_target_property(Activemq-cpp_INCLUDE_DIRS Activemq-cpp Activemq-cpp_INCLUDE_DIRS)
get_target_property(Activemq-cpp_LIBRARIES Activemq-cpp Activemq-cpp_LIBRARIES)

target_include_directories(cms
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${Activemq-cpp_INCLUDE_DIRS}
        PUBLIC ${Apr_INCLUDE_DIRS})

message(STATUS "Apr Include: ${Apr_INCLUDE_DIRS}")
message(STATUS "Apr-util Include: ${Apr-util_INCLUDE_DIRS}")
message(STATUS "Activemq-cpp Include: ${Activemq-cpp_INCLUDE_DIRS}")
message(STATUS "Apr libraries: ${Apr_LIBRARIES}")
message(STATUS "Apr-util libraries: ${Apr-util_LIBRARIES}")
message(STATUS "Activemq-cpp libraries: ${Activemq-cpp_LIBRARIES}")

target_link_libraries(cms ${Apr_LIBRARIES} ${Activemq-cpp_LIBRARIES} ${Apr-util_LIBRARIES})
