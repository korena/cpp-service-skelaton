#ifndef _HELLOWORLDCONSUMER_HPP_
#define _HELLOWORLDCONSUMER_HPP_

#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>

class HelloWorldConsumer : public cms::ExceptionListener,
                           public cms::MessageListener,
                           public decaf::lang::Runnable {

private:

    decaf::util::concurrent::CountDownLatch latch;
    decaf::util::concurrent::CountDownLatch doneLatch;
    cms::Connection* connection;
    cms::Session* session;
    cms::Destination* destination;
    cms::MessageConsumer* consumer;
    long waitMillis;
    bool useTopic;
    bool sessionTransacted;
    std::string brokerURI;

private:

    HelloWorldConsumer(const HelloWorldConsumer&);
    HelloWorldConsumer& operator=(const HelloWorldConsumer&);

public:

    HelloWorldConsumer(const std::string& brokerURI, int numMessages, bool useTopic = false, bool sessionTransacted = false, int waitMillis = 30000);

    virtual ~HelloWorldConsumer() {
        cleanup();
    }

    void close() {
        this->cleanup();
    }

    void waitUntilReady() {
        latch.await();
    }

    virtual void run();

    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage(const cms::Message* message);

    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException(const cms::CMSException& ex AMQCPP_UNUSED);

private:

    void cleanup();
};

#endif
