# build all third party projects, because I will NEVER do a super build that
# forces me to consider my project a f**king external project .. EVER.

cmake_minimum_required(VERSION 3.12)

project(service_thirdParty)

message(STATUS "Pre-processing third party libraries")

# cmake friendly (LoadPrefixPath.cmake.in will update CMAKE_PREFIX_PATH for these)

# zlib
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/zlib)
get_target_property(local_zlib_INSTALL_PREFIX local_zlib local_zlib_INSTALL_PREFIX)
get_target_property(local_zlib_INSTALL local_zlib local_zlib_INSTALL)
# gRPC
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gRPC)

get_target_property(protobuf_INSTALL_PREFIX protobuf protobuf_INSTALL_PREFIX)
get_target_property(c-ares_INSTALL_PREFIX c-ares c-ares_INSTALL_PREFIX)
get_target_property(grpc_INSTALL_PREFIX grpc grpc_INSTALL_PREFIX)

# gtest suite
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)
get_target_property(googletest_INSTALL_PREFIX googletest googletest_INSTALL_PREFIX)

# rapidJSON
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rapidJSON)
get_target_property(rapidJSON_INSTALL_PREFIX rapidJSON rapidJSON_INSTALL_PREFIX)


# cmake unfriendly (LoadPrefixPath.cmake.in will use set command for these)
# Activemq-cpp
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Apr) # needs local_zlib_INSTALL_PREFIX
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Apr-util)
get_target_property(Apr_INSTALL_PREFIX Apr Apr_INSTALL_PREFIX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Activemq_cpp) # needs Apr_INSTALL_PREFIX
get_target_property(Activemq-cpp_INSTALL_PREFIX Activemq-cpp Activemq-cpp_INSTALL_PREFIX)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/LoadPrefixPath.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/LoadPrefixPath.cmake")
