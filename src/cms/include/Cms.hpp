#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/library/ActiveMQCPP.h>
#include <activemq/util/Config.h>
#include <cms/BytesMessage.h>
#include <cms/Connection.h>
#include <cms/ExceptionListener.h>
#include <cms/MapMessage.h>
#include <cms/MessageListener.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/Runnable.h>
#include <decaf/lang/System.h>
#include <decaf/lang/Thread.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

#include "HelloWorldConsumer.hpp"
#include "HelloWorldProducer.hpp"


int helloWorldCms(void);


