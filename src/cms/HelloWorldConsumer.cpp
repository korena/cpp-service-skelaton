#include <utility>

#include "HelloWorldConsumer.hpp"
#include "HelloWorldProducer.hpp"

    HelloWorldConsumer::HelloWorldConsumer(std::string  brokerURI, int numMessages, bool useTopic, bool sessionTransacted, int waitMillis) :
        latch(1),
        doneLatch(numMessages),
        connection(nullptr),
        session(nullptr),
        destination(nullptr),
        consumer(nullptr),
        waitMillis(waitMillis),
        useTopic(useTopic),
        sessionTransacted(sessionTransacted),
        brokerURI(std::move(brokerURI)) {
    }

    void HelloWorldConsumer::run() {

        try {

            // Create a ConnectionFactory
            std::unique_ptr<cms::ConnectionFactory> connectionFactory(
                cms::ConnectionFactory::createCMSConnectionFactory(brokerURI));

            // Create a Connection
            connection = connectionFactory->createConnection();
            connection->start();
            connection->setExceptionListener(this);

            // Create a Session
            if (this->sessionTransacted) {
                session = connection->createSession(cms::Session::SESSION_TRANSACTED);
            } else {
                session = connection->createSession(cms::Session::AUTO_ACKNOWLEDGE);
            }

            // Create the destination (Topic or Queue)
            if (useTopic) {
                destination = session->createTopic("TEST.FOO");
            } else {
                destination = session->createQueue("TEST.FOO");
            }

            // Create a MessageConsumer from the Session to the Topic or Queue
            consumer = session->createConsumer(destination);

            consumer->setMessageListener(this);

            std::cout.flush();
            std::cerr.flush();

            // Indicate we are ready for messages.
            latch.countDown();

            // Wait while asynchronous messages come in.
            doneLatch.await(waitMillis);

        } catch (cms::CMSException& e) {
            // Indicate we are ready for messages.
            latch.countDown();
            e.printStackTrace();
        }
    }

    // Called from the consumer since this class is a registered MessageListener.
    void HelloWorldConsumer::onMessage(const cms::Message* message) {

        static int count = 0;

        try {
            count++;
            const auto* textMessage = dynamic_cast<const cms::TextMessage*> (message);
            std::string text;

            if (textMessage != nullptr) {
                text = textMessage->getText();
            } else {
                text = "NOT A TEXTMESSAGE!";
            }

            printf("Message #%d Received: %s\n", count, text.c_str());

        } catch (cms::CMSException& e) {
            e.printStackTrace();
        }

        // Commit all messages.
        if (this->sessionTransacted) {
            session->commit();
        }

        // No matter what, tag the count down latch until done.
        doneLatch.countDown();
    }

    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
     void HelloWorldConsumer::onException(const cms::CMSException& ex AMQCPP_UNUSED) {
        printf("CMS Exception occurred.  Shutting down client.\n");
        ex.printStackTrace();
        exit(1);
    }

    void HelloWorldConsumer::cleanup() {
        if (connection != nullptr) {
            try {
                connection->close();
            } catch (cms::CMSException& ex) {
                ex.printStackTrace();
            }
        }

        // Destroy resources.
        try {
            delete destination;
            destination = nullptr;
            delete consumer;
            consumer = nullptr;
            delete session;
            session = nullptr;
            delete connection;
            connection = nullptr;
        } catch (cms::CMSException& e) {
            e.printStackTrace();
        }
    }
