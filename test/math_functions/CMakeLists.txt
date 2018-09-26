add_executable(mathFunctionsTest mathFunctionsTest.cpp)

find_package(GTest CONFIG REQUIRED)

if(GTest_FOUND)
    message(STATUS "using GTest ${GTest_VERSION}")
endif(GTest_FOUND)

target_link_libraries(mathFunctionsTest mathFunctions GTest::gtest_main)
add_test(NAME BASIC COMMAND mathFunctionsTest)
