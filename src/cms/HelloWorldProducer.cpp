#include "./include/HelloWorldProducer.hpp"
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
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

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;


    Connection* connection;
    Session* session;
    Destination* destination;
    MessageProducer* producer;
    int numMessages;
    bool useTopic;
    bool sessionTransacted;
    std::string brokerURI;

    HelloWorldProducer::HelloWorldProducer(const std::string& brokerURI, int numMessages, bool useTopic, bool sessionTransacted) :
        connection(NULL),
        session(NULL),
        destination(NULL),
        producer(NULL),
        numMessages(numMessages),
        useTopic(useTopic),
        sessionTransacted(sessionTransacted),
        brokerURI(brokerURI) {
    }

    void HelloWorldProducer::close() {
        this->cleanup();
    }

    void HelloWorldProducer::run() {

        try {

            // Create a ConnectionFactory
            auto_ptr<ConnectionFactory> connectionFactory(
                ConnectionFactory::createCMSConnectionFactory(brokerURI));

            // Create a Connection
            connection = connectionFactory->createConnection();
            connection->start();

            // Create a Session
            if (this->sessionTransacted) {
                session = connection->createSession(Session::SESSION_TRANSACTED);
            } else {
                session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
            }

            // Create the destination (Topic or Queue)
            if (useTopic) {
                destination = session->createTopic("TEST.FOO");
            } else {
                destination = session->createQueue("TEST.FOO");
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            producer = session->createProducer(destination);
            producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);

            // Create the Thread Id String
            string threadIdStr = Long::toString(Thread::currentThread()->getId());

            // Create a messages
            string text = (string) "Hello world! from thread " + threadIdStr;

            for (int ix = 0; ix < numMessages; ++ix) {
                std::auto_ptr<TextMessage> message(session->createTextMessage(text));
                message->setIntProperty("Integer", ix);
                printf("Sent message #%d from thread %s\n", ix + 1, threadIdStr.c_str());
                producer->send(message.get());
            }

        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }

    void HelloWorldProducer::cleanup() {

        if (connection != NULL) {
            try {
                connection->close();
            } catch (cms::CMSException& ex) {
                ex.printStackTrace();
            }
        }

        // Destroy resources.
        try {
            delete destination;
            destination = NULL;
            delete producer;
            producer = NULL;
            delete session;
            session = NULL;
            delete connection;
            connection = NULL;
        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }

