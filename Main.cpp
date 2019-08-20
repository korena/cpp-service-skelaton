#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <pthread.h>

#include "ServiceConfig.h"

#ifdef USE_MYMATH

#include "mathFunctions.h"

#endif

#include "Cms.hpp"
#include "greeter_async_server.h"
#include "greeter_async_client.h"

void *run_async_server(void *) {
    ServerImpl server;
    server.Run();

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    std::cout << "Service version (" << SERVICE_VERSION_MAJOR << "." << SERVICE_VERSION_MINOR << ")" << std::endl;

    /* CMS demo (requires Activemq broker running with default ports) */
    std::cout << "================== C++ messaging service demo (START) ==================" << std::endl;
    helloWorldCms();
    std::cout << "================== C++ messaging service demo (END)   ==================" << std::endl;
    /* gRPC demo (starts a server in a separate thread, and a client in the current main thread) */
    std::cout << "==================      gRPC Async demo (START)       ==================" << std::endl;
    /* Create thread for gRPC async server, note: don't do threads this way. */
    pthread_t server_thread;
    if (pthread_create(&server_thread, nullptr, run_async_server, nullptr) != 0) {
        std::cout << "Could not create a thread for gRPC server, sh*t happens." << std::endl;
        return 1; // couldn't create thread!
    }

    /* Create and run gRPC async client */

    /* Instantiate the client. It requires a channel, out of which the actual RPCs
     * are created. This channel models a connection to an endpoint (in this case,
     * localhost at port 50051). We indicate that the channel isn't authenticated
     * (use of InsecureChannelCredentials()).
     */
    GreeterClient greeter(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);  // The actual RPC call!
    std::cout << "Greeter received: " << reply << std::endl;

    std::cout << "==================       gRPC Async demo (END)        ==================" << std::endl;

    std::cout << "==================     User libraries demo (START)    ==================" << std::endl;
    if (argc == 2) {

        char *ptr;
        double inputValue = strtod(argv[1], &ptr);

#ifdef USE_MYMATH
        double outputValue = mySqrt(inputValue);
#else
        double outputValue = sqrt(inputValue);
#endif

        fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);
    } else {
        fprintf(stdout, "Failed to run Maths function demo, Usage: %s (number)\n", argv[0]);
    }
    std::cout << "==================      User libraries demo (END)     ==================" << std::endl;
    pthread_exit(nullptr);
}
