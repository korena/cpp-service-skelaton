#include "include/Cms.hpp"


int helloWorldCms() {

    activemq::library::ActiveMQCPP::initializeLibrary();
    {
        std::string brokerURI =
                "failover:(tcp://localhost:61616)";

        //============================================================
        // set to true to use topics instead of queues
        // Note in the code above that this causes createTopic or
        // createQueue to be used in both consumer an producer.
        //============================================================
        bool useTopics = false;
        bool sessionTransacted = false;
        int numMessages = 2000;

        long long startTime = decaf::lang::System::currentTimeMillis();

        HelloWorldProducer producer(brokerURI, numMessages, useTopics);
        HelloWorldConsumer consumer(brokerURI, numMessages, useTopics, sessionTransacted);

        // Start the consumer thread.
        decaf::lang::Thread consumerThread(&consumer);
        consumerThread.start();

        // Wait for the consumer to indicate that its ready to go.
        consumer.waitUntilReady();

        // Start the producer thread.
        decaf::lang::Thread producerThread(&producer);
        producerThread.start();

        // Wait for the threads to complete.
        producerThread.join();
        consumerThread.join();

        long long endTime = decaf::lang::System::currentTimeMillis();
        double totalTime = (double)(endTime - startTime) / 1000.0;

        consumer.close();
        producer.close();

        std::cout << "Time to completion = " << totalTime << " seconds." << std::endl;
    }
    activemq::library::ActiveMQCPP::shutdownLibrary();

    return 0;
}