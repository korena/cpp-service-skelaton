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
    message( WARNING "setup.cmake")
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
Create a directory in `third_party/` to host everything you need to actually build that library. This will not host
the source code of your library, never include source code that is not yours in the repository, instead, write logic in
your library's specific build instructions to fetch it from somewhere.

## 2. CMakeLists.txt file, you must write
Create a CMakeLists.txt file in the library's directory, and write your externalProject commands to build it, you
can see `third_party/zlib/CMakeLists.txt` for an example of a CMake friendly library, and 
`third_party/Activemq_cpp/CMakeLists.txt` for an ugly autoconf example. You're not limited to this, but understanding 
both those examples should lead you anywhere you want to go, with a bit of CMake RTFM-ing of course.

## 3. third_party/CMakeLists.txt, you must modify

Add a `add_subdirectory()` entry to `third_party/CMakeLists.txt` so it will pick up and process your library's build 
instructions.
Note that the order of things matter, take the example of zlib and Apr, `third_party/Apr/CMakeLists.txt` needs to pass
an argument called `local_zlib_INSTALL_PREFIX` to Apr's config script, so this line:
 `get_target_property(local_zlib_INSTALL_PREFIX local_zlib local_zlib_INSTALL_PREFIX)`
needs to appear in third_party/CMakeLists.txt BEFORE the line `add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Apr)` , so
we it would be defined when Apr's `third_party/Apr/CMakeLists.txt` is executed. 
Now where does `local_zlib_INSTALL_PREFIX` come from? Well, it comes from executing `third_party/zlib/CMakeLists.txt`,
which is why the line `add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/zlib)` appears BEFORE the line 
`get_target_property(local_zlib_INSTALL_PREFIX local_zlib local_zlib_INSTALL_PREFIX)` in `third_party/CMakeLists.txt`.

## 4. For find_package command, you must prepare

Depending on your library's friendliness to CMake:

### 4.1 CMake unfriendly library
 If your library is not CMake friendly, you need to write a `Find${LibraryName}Module.cmake` and place it in the 
`modules/` directory so your source code can locate it later using `find_package(LibraryName MODULE)`, you can check
the examples that are already there for Apr and Activemq-cpp libraries.

In the existing examples, you can see a variable being used in the `modules/` directory find scripts, something like
`<some-name>_ROOT_DIR`, these are delivered to the find script in the following way:
1. `third_party/<library-directory>/CMakeLists.txt` file exports the `install_dir` of the library in question
2. `third_party/CMakeLists.txt` file uses `get_target_property` to fetch the exported `install_dir` variable from the 
library target.
3. `LoadPrefixPath.cmake.in` script contains calls to `set(...)` command for each library, which defines the
`<some-name>_ROOT_DIR` variable.
4. That variable is then referenced in the find script.

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
        
