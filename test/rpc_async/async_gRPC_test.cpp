#include <iostream>

#include "gtest/gtest.h"
#include "greeter_async_server.h"
#include "greeter_async_client.h"
#include "adhoc_threads.h"


#define SERVER_THREAD_ID long(0)
#define CLIENT_THREAD_ID long(1)

const static std::string EXPECTED_REPLY{"Hello world"};

namespace {

    ServerImpl server;

    void *server_task(void *) {
        server.Run();
        pthread_exit(nullptr);
    }

    void *client_task(void *thread_data) {
        auto pth_data = (THREAD_DATA*) thread_data;
        GreeterClient greeter(grpc::CreateChannel(
                "localhost:50051", grpc::InsecureChannelCredentials()));
        std::string user("world");
        std::string reply = greeter.SayHello(user);  // The actual RPC call!
        std::cout << "Greeter received: " << reply << std::endl;
        pth_data->status = (reply == EXPECTED_REPLY);
        pthread_exit(nullptr);
    }

    TEST(async_gRPC_test, BASIC) {
        // Create server thread and start it
        char s[MAX_CHAR];
        sprintf(s, "Async gRPC Server Thread");
        set_thread_data(SERVER_THREAD_ID, s);
        create_default_thread(&threads_data[SERVER_THREAD_ID], server_task, HIGH);
        // Create client thread and start it
        sprintf(s, "Async gRPC Client Thread");
        set_thread_data(CLIENT_THREAD_ID, s);
        create_default_thread(&threads_data[CLIENT_THREAD_ID], client_task, HIGH);

        free_thread_stuff();
        sleep(1);
        server.quit(); // exchange of greeting is expected to be done by now, so stop the server processing loop.

        int rc;
        for(int i= MAX_THREADS_NO-1; i >= 0; --i) {
            // wait for thread to join and return its status.
            std::cout << "waiting for thread (" << threads_data[i].thread_info.name << ") to join" << std::endl;
            rc = pthread_join(threads[i], nullptr);
            check(rc == 0, "Could not join %s", threads_data[i].thread_info.name)
            std::cout << "Joined thread (" << threads_data[i].thread_info.name << ")" << std::endl;
        }

        EXPECT_EQ(true, threads_data[CLIENT_THREAD_ID].status);

    }

}  // namespace
