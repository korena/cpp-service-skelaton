# A client library to interact with activemq
# expects both openssl and libuuid to be installed .. a reasonable expectation ..

include(ExternalProject)

set(Activemq-cpp_PREFIX 3.9.4)

ExternalProject_Add(Activemq-cpp
        PREFIX ${Activemq-cpp_PREFIX}
        GIT_REPOSITORY https://github.com/korena/activemq-cpp.git
        GIT_TAG ${Activemq-cpp_PREFIX}
        UPDATE_COMMAND "" # do not f**king rebuild if not needed!
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}
        BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}
        INSTALL_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}
        # For some unknown reason (to me),
        # the following line disables the annoying "rebuild regardless of sh*t" attitude of ExternalProject"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${Activemq-cpp_PREFIX}
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

ExternalProject_Get_Property(Activemq-cpp install_dir)

message(STATUS "Setting Activemq-cpp properties to be shared ...")
# Set your own properties you useless c word.

file(GLOB_RECURSE LIBRARIES ${install_dir}/lib/*.a ${install_dir}/lib/*.dylib )

set(Activemq-cpp_INCLUDE_DIRS ${install_dir}/include/activemq-cpp-${Activemq-cpp_PREFIX})

set_target_properties( Activemq-cpp
        PROPERTIES
        Activemq-cpp_INCLUDE_DIRS "${Activemq-cpp_INCLUDE_DIRS}"
        Activemq-cpp_LIBRARIES "${LIBRARIES}")
