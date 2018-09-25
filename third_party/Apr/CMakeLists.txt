# Apache Portable Runtime Project (dependency of activemq-cpp)

include(ExternalProject)

set(Apr_PREFIX 1.6.5)

ExternalProject_Add(Apr
        PREFIX ${Apr_PREFIX}
        GIT_REPOSITORY https://github.com/korena/apr.git
        GIT_TAG ${Apr_PREFIX}
        UPDATE_COMMAND "" # do not f**king rebuild if not needed!
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr_PREFIX}
        BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr_PREFIX}
        INSTALL_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr_PREFIX}
        # For some unknown reason (to me),
        # the following line disables the annoying "rebuild regardless of sh*t" attitude of ExternalProject"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${Apr_PREFIX}
        )

# making s**t executable
ExternalProject_Add_Step(Apr chmodConfig
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/config_hell.sh
        COMMENT "chmod +x *.sh files to prepare for configuration"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Apr chmodBuild
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/build_hell.sh
        COMMENT "chmod +x *.sh files to prepare for building"
        DEPENDEES download # run chmodConfig after download
        )

ExternalProject_Add_Step(Apr chmodInstall
        COMMAND  chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/install_hell.sh
        COMMENT "chmod +x *.sh files to prepare for installation"
        DEPENDEES download # run chmodConfig after download
        )

# Apr
ExternalProject_Get_Property(Apr install_dir)
set(Apr_INST_PREFIX "${install_dir}")
set_target_properties( Apr
        PROPERTIES
        Apr_INSTALL_PREFIX "${Apr_INST_PREFIX}")
