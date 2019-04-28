#ifndef HELLOWORLDPRODUCER_HPP
#define HELLOWORLDPRODUCER_HPP

#include <decaf/lang/Runnable.h>
#include <cms/Connection.h>
#include <cms/Session.h>

class HelloWorldProducer : public decaf::lang::Runnable {
private:
 
    cms::Connection* connection;
    cms::Session* session;
    cms::Destination* destination;
    cms::MessageProducer* producer;
    int numMessages;
    bool useTopic;
    bool sessionTransacted;
    std::string brokerURI;
 
private:
 
    HelloWorldProducer(const HelloWorldProducer&);
    HelloWorldProducer& operator=(const HelloWorldProducer&);
 
public:
 
    HelloWorldProducer(std::string  brokerURI, int numMessages, bool useTopic = false, bool sessionTransacted = false);
 
    ~HelloWorldProducer() override{
        cleanup();
    }
 
    void close();
 
    void run() override;
 
private:

    void cleanup();
};

#endif /* HELLOWORLDPRODUCER_HPP */

