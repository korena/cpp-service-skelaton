# rapidJSON header only library

include(ExternalProject)

set(rapidJSON_PREFIX v1.1.0)

ExternalProject_Add(rapidJSON
        PREFIX ${rapidJSON_PREFIX}
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG ${rapidJSON_PREFIX}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${rapidJSON_PREFIX}
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_THIRDPARTY_GTEST=OFF
        )

# rapidJSON
ExternalProject_Get_Property(rapidJSON install_dir)
set(rapidJSON_INST_PREFIX "${install_dir}")
set_target_properties( rapidJSON
        PROPERTIES
        rapidJSON_INSTALL_PREFIX "${rapidJSON_INST_PREFIX}")
