add_library(mathFunctions STATIC mathFunctions.cpp)

# Note: all internal source code includes should be public if we want them to be accessible to other
# parts for the code.
target_include_directories(mathFunctions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)