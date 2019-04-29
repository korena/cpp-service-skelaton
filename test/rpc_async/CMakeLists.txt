add_executable(async_gRPC_test async_gRPC_test.cpp)

find_package(GTest CONFIG REQUIRED)
#find_package(Protobuf CONFIG REQUIRED)
#find_package(gRPC CONFIG REQUIRED)

if(GTest_FOUND)
    message(STATUS "using GTest ${GTest_VERSION}")
endif(GTest_FOUND)

target_link_libraries(async_gRPC_test
        GTest::gtest_main
        greeter_async_client
        greeter_async_server)
