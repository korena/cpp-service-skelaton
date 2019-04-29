#include <iostream>

#include "gtest/gtest.h"
#include "greeter_async_server.h"
#include "greeter_async_client.h"


// TODO: finish this
namespace {

    TEST(async_gRPC_test, BASIC) {
        // create server
        ServerImpl server;
        server.Run();
    }

}  // namespace


