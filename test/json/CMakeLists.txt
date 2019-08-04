add_executable(jsonTest jsonTest.cpp)

find_package(GTest CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

if(GTest_FOUND)
    message(STATUS "using GTest ${GTest_VERSION}")
endif(GTest_FOUND)

target_include_directories(jsonTest PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_link_libraries(jsonTest GTest::gtest_main)
add_test(NAME BASIC COMMAND mathFunctionsTest)
