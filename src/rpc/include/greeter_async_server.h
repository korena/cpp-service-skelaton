#ifndef SERVICE_GREETER_ASYNC_SERVER_H
#define SERVICE_GREETER_ASYNC_SERVER_H

#include <memory>
#include <iostream>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "service.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class ServerImpl final {
public:
    ~ServerImpl();

    // There is no shutdown handling in this code.
    void Run();

private:
    // Class encompassing the state and logic needed to serve a request.
    class CallData {
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq);

        void Proceed();

    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        Greeter::AsyncService* service_;
        // The producer-consumer queue where for asynchronous server notifications.
        ServerCompletionQueue* cq_;
        // Context for the rpc_async, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        ServerContext ctx_;

        // What we get from the client.
        HelloRequest request_;
        // What we send back to the client.
        HelloReply reply_;

        // The means to get back to the client.
        ServerAsyncResponseWriter<HelloReply> responder_;

        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // The current serving state.
    };

    // This can be run in multiple threads if needed.
    void HandleRpcs();

    std::unique_ptr<ServerCompletionQueue> cq_;
    Greeter::AsyncService service_;
    std::unique_ptr<Server> server_;
};


#endif //SERVICE_GREETER_ASYNC_SERVER_H
