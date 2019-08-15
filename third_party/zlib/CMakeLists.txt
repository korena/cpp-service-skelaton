# rapidJSON header only library

include(ExternalProject)

set(local_zlib_PREFIX v1.2.11)

ExternalProject_Add(local_zlib
        PREFIX ${local_zlib_PREFIX}
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG ${local_zlib_PREFIX}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/zlib
        )

# zlib
ExternalProject_Get_Property(local_zlib install_dir)
set(local_zlib_INST_PREFIX "${install_dir}")
set_target_properties( local_zlib
        PROPERTIES
        local_zlib_INSTALL_PREFIX "${local_zlib_INST_PREFIX}")

set_target_properties(local_zlib
        PROPERTIES
        local_zlib_INSTALL "${CMAKE_CURRENT_BINARY_DIR}")
