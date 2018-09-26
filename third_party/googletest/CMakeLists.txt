# gtest testing framework

include(ExternalProject)

set(googletest_PREFIX release-1.8.1)

ExternalProject_Add(googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG  ${googletest_PREFIX}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${googletest_PREFIX}
        )

# googletest
set(googletest_INST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${googletest_PREFIX}")
message(STATUS "googletest_INST_PREFIX : ${googletest_INST_PREFIX}")
set_target_properties( googletest
        PROPERTIES
        googletest_INSTALL_PREFIX "${googletest_INST_PREFIX}")
