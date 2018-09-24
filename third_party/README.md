# How is this working?

Well, the top CMakeLists.txt file has the following snippet at the top:

```cmake
if((NOT EXISTS "${CMAKE_BINARY_DIR}/third_party/LoadPrefixPath.cmake") OR ("${FORCE_THIRD_PARTY_BUILD}"))
    # execute another process to configure all third party libraries
    execute_process(
            COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -G ${CMAKE_GENERATOR} -H. -B${CMAKE_BINARY_DIR}/third_party
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/third_party)
    # execute another process to build all third party libraries (only if we don't have them!)
    execute_process(
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/third_party
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/third_party)
else((NOT EXISTS "${CMAKE_BINARY_DIR}/third_party/LoadPrefixPath.cmake") OR ("${FORCE_THIRD_PARTY_BUILD}"))
    message( WARNING "Skipping third party libraries configuration and build, check FORCE_THIRD_PARTY_BUILD in the root CMakeLists.txt if this isn't what you expect.")
endif((NOT EXISTS "${CMAKE_BINARY_DIR}/third_party/LoadPrefixPath.cmake") OR ("${FORCE_THIRD_PARTY_BUILD}"))
```

This basically runs two execute_process commands to configure and build and install all third party libraries in this
directory.


# How do I add another third party library?

You need to first know how to build/install that library, if its CMake friendly, you're in luck, otherwise, you'll have 
to figure out the exact commands that need to be executed to produce usable binaries out of that library.

All third party libraries are built using CMake's ExternalProject, regardless of whether they support CMake builds or
not, because ExternalProject is an extraordinary tool. So here are the steps:

## 1. Directory, you must create
Create a directory in `third_party/` to host everything you need to actually build that library. This will not host the
the source code of your library, never include source code that is not yours in the repository, instead, right logic in
your library's specific build instructions to fetch it from somewhere,

## 2. CMakeLists.txt file, you must write
Create a CMakeLists.txt file in your library's directory, and write your externalProject commands to build it, you
can see `third_party/gRPC/CMakeLists.txt` for an example of a CMake friendly library, and 
`third_party/Activemq_cpp/CMakeLists.txt` for an ugly autoconf example. You're not limited to this, but understanding 
both those examples should lead you anywhere you want to go, with a bit of CMake RTFM-ing of course.

## 3. third_party/CMakeLists.txt, you must modify

Add a `add_subdirectory()` entry to `third_party/CMakeLists.txt` so it will pick up and process your library's build 
instructions.

## 4. For find_package command, you must prepare

Depending on your library's friendliness to CMake:

### 4.1 CMake unfriendly library
 If your library is not CMake friendly, you need to write a Find${LibraryName}Module.cmake and place it in the 
`modules/` directory so your source code can locate it later using `find_package(LibraryName MODULE)`, you can check
the examples that are already there for Apr and Activemq-cpp libraries.

### 4.2 CMake friendly library
If your library is CMake friendly, it will produce some sort of a config/module file that can be used by
find_package family of commands.

### 4.2.1 Config files
If it's a config file (looks like `LibraryNameConfig.cmake` or `LibraryName-config.cmake`):
1. Use `ExternalProject_Get_Property(libraryTargetName install_dir)` in the new library's CMakeLists.txt file to get the
 install directory of your library, and fetch it from `third_party/CMakeLists.txt` using `get_target_property` 
 command like other libraries are doing.
         
2. Edit the file `third_party/LoadPrefixPath.cmake.in` and add the installation prefix of your built library to the 
list that is being appended to `CMAKE_PREFIX_PATH`, follow the examples already there.

3. In the CMakeLists.txt file of the source code that will use this library, use `find_package(LibraryName CONFIG)`
        to locate it and use it, follow the example of usage of gRPC library in `src/rpc/CMakeLists.txt`.
        
### 4.2.2 Module files
add the directory in which that module file is created to `CMAKE_MODULE_PATH`.


# Why not use the config/module stuff that ship with CMake?

That's only useful for things that you require as pre-requisites (such as openssl in this project), but if you built and
installed it, and your repository carries its build and install instructions, you handle its find_package command 
compliance!
        
