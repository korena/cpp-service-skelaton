# A client library to interact with activemq
# expects both openssl and libuuid to be installed .. a reasonable expectation ..

include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)

set(Activemq-cpp_PREFIX activemq-cpp-3.9.5)

ExternalProject_Add(Activemq-cpp
        PREFIX ${Activemq-cpp_PREFIX}
        GIT_REPOSITORY https://github.com/apache/activemq-cpp.git
        GIT_TAG ${Activemq-cpp_PREFIX}
        UPDATE_COMMAND "" # do not f**king rebuild if not needed!
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX} ${Apr_INSTALL_PREFIX} ${local_zlib_INSTALL}
        BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}
        INSTALL_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}
        # For some unknown reason (to me),
        # the following line disables the annoying "rebuild regardless of sh*t" attitude of ExternalProject"
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${Activemq-cpp_PREFIX}
        DEPENDS Apr Apr-util
        )


# making s**t executable
ExternalProject_Add_Step(Activemq-cpp chmodConfig
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh
        COMMENT "chmod +x *.sh files to prepare for configuration"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Activemq-cpp chmodBuild
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh
        COMMENT "chmod +x *.sh files to prepare for building"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Activemq-cpp chmodInstall
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh
        COMMENT "chmod +x *.sh files to prepare for installation"
        DEPENDEES download # run chmodConfig after download
        )

# Activemq-cpp
ExternalProject_Get_Property(Activemq-cpp install_dir)
set(Activemq-cpp_INST_PREFIX "${install_dir}")
set_target_properties( Activemq-cpp
        PROPERTIES
        Activemq-cpp_INSTALL_PREFIX "${Activemq-cpp_INST_PREFIX}")
