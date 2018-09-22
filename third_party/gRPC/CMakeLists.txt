include(ExternalProject)

# third party libraries install directory
# Note: For all external dependencies, instead of using checked-out code, one could
# specify GIT_REPOSITORY and GIT_TAG to have cmake download the dependency directly,
# without needing to add a submodule to your project.

ExternalProject_Add(c-ares
  PREFIX c-ares
  GIT_REPOSITORY https://github.com/c-ares/c-ares.git
  GIT_TAG 3be1924221
  CMAKE_CACHE_ARGS
        -DCARES_SHARED:BOOL=OFF
        -DCARES_STATIC:BOOL=ON
        -DCARES_STATIC_PIC:BOOL=ON
        -DCMAKE_INSTALL_PREFIX:PATH=c-ares
)

# Builds protobuf project from the git submodule.
ExternalProject_Add(protobuf
  PREFIX protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG 48cb18e5
  SOURCE_SUBDIR cmake
  CMAKE_CACHE_ARGS
        -Dprotobuf_BUILD_TESTS:BOOL=OFF
        -Dprotobuf_WITH_ZLIB:BOOL=OFF
        -Dprotobuf_MSVC_STATIC_RUNTIME:BOOL=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=protobuf
)

# Builds zlib project from the git submodule.
ExternalProject_Add(zlib
  PREFIX zlib
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_TAG cacf7f1d4e
  CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_INST_DIR}/zlib
)

# the location where protobuf-config.cmake will be installed varies by platform
if (WIN32)
  set(_FINDPACKAGE_PROTOBUF_CONFIG_DIR "${THIRD_PARTY_INST_DIR}/protobuf/cmake")
else()
  set(_FINDPACKAGE_PROTOBUF_CONFIG_DIR "${THIRD_PARTY_INST_DIR}/protobuf/lib/cmake/protobuf")
endif()

# Builds gRPC and set arguments so that all the dependencies
# are correctly located.
ExternalProject_Add(grpc
  PREFIX grpc
  GIT_REPOSITORY https://github.com/grpc/grpc.git
  GIT_TAG v1.15.0
  CMAKE_CACHE_ARGS
        -DgRPC_INSTALL:BOOL=ON
        -DgRPC_BUILD_TESTS:BOOL=OFF
        -DgRPC_PROTOBUF_PROVIDER:STRING=package
        -DgRPC_PROTOBUF_PACKAGE_TYPE:STRING=CONFIG
        -DProtobuf_DIR:PATH=${_FINDPACKAGE_PROTOBUF_CONFIG_DIR}
        -DgRPC_ZLIB_PROVIDER:STRING=package
        -DZLIB_ROOT:STRING=zlib
        -DgRPC_CARES_PROVIDER:STRING=package
        -Dc-ares_DIR:PATH=c-ares/lib/cmake/c-ares
        -DgRPC_SSL_PROVIDER:STRING=package
        ${_CMAKE_ARGS_OPENSSL_ROOT_DIR}
        -DCMAKE_INSTALL_PREFIX:PATH=grpc
  DEPENDS c-ares protobuf zlib
)


# You can now build the actual application itself as an external project using a CMakeLists.txt that assumes all the dependencies
# have already been installed.

# If we wanted to reuse the targets exported by gRPC and protobuf, we could have built analyzer application
# here, as another ExternalProject_Add, but we know that analyzer application is not really an external 
# project, but the actual executable that we expect, so we're not going to do that, instead, we will 
# keep this CMakeLists.txt file to handle all the really external stuff that we depend on, and we'll manually
# import the ${THIRD_PARTY_INST_DIR}/{grpc,protobuf} dependencies in the CMakeLists.txt file that lives in 
# src directory, because that makes more sense .. structurally. 