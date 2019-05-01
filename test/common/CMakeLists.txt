add_library(test_common STATIC adhoc_threads.cpp)
target_include_directories(test_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
