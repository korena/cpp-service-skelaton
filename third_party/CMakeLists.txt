# build all third party projects, because I will NEVER do a super build that
# forces me to consider my project a f**king external project .. EVER.

cmake_minimum_required(VERSION 3.12)

message(STATUS "Pre-processing third party libraries")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Apr)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Apr-util)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Activemq_cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gRPC)


get_target_property(protobuf_INSTALL_PREFIX protobuf protobuf_INSTALL_PREFIX)
get_target_property(zlib_INSTALL_PREFIX zlib zlib_INSTALL_PREFIX)
get_target_property(c-ares_INSTALL_PREFIX c-ares c-ares_INSTALL_PREFIX)
get_target_property(grpc_INSTALL_PREFIX grpc grpc_INSTALL_PREFIX)

get_target_property(Apr_INSTALL_PREFIX Apr Apr_INSTALL_PREFIX)
get_target_property(Activemq-cpp_INSTALL_PREFIX Activemq-cpp Activemq-cpp_INSTALL_PREFIX)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/LoadPrefixPath.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/LoadPrefixPath.cmake")
