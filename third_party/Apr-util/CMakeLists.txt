# Apache Portable Runtime Project (dependency of activemq-cpp)

include(ExternalProject)

set(Apr-util_PREFIX 1.6.1)

ExternalProject_Add(Apr-util
        PREFIX ${Apr-util_PREFIX}
        GIT_REPOSITORY https://github.com/korena/apr-util.git
        GIT_TAG ${Apr-util_PREFIX}
        UPDATE_COMMAND "" # do not f**king rebuild if not needed!
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr-util_PREFIX}
        BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr-util_PREFIX}
        INSTALL_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr-util_PREFIX}
        # For some unknown reason (to me),
        # the following line disables the annoying "rebuild regardless of sh*t" attitude of ExternalProject"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${Apr-util_PREFIX}
        )

# making s**t executable
ExternalProject_Add_Step(Apr-util chmodConfig
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh
        COMMENT "chmod +x *.sh files to prepare for configuration"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Apr-util chmodBuild
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh
        COMMENT "chmod +x *.sh files to prepare for building"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Apr-util chmodInstall
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh
        COMMENT "chmod +x *.sh files to prepare for installation"
        DEPENDEES download # run chmodConfig after download
        )

#ExternalProject_Get_Property(Apr-util install_dir)
#
#message(STATUS "Setting Apr-util properties to be shared ...")
## Set your own properties you useless c word.
#file(GLOB Apr-util_LIBRARIES ${install_dir}/lib/*.a ${install_dir}/lib/*.dylib)
#
#
#set_target_properties( Apr-util
#        PROPERTIES
#        Apr-util_INCLUDE_DIRS "${install_dir}/include/apr-1"
#        Apr-util_LIBRARIES "${Apr-util_LIBRARIES}")