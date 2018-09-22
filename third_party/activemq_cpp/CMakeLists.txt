# A client library to interact with activemq

include(ExternalProject)

ExternalProject_Add(activemq-cpp
        PREFIX activemq-cpp
        GIT_REPOSITORY https://github.com/korena/activemq-cpp.git
        GIT_TAG 3.9.4
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/configure --prefix=lib
        BUILD_COMMAND ${MAKE}
        INSTALL_COMMAND ${MAKE} install
        DEPENDS Apr
        )
