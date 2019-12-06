# What is this?

This is a scaffolding project for the purpose of building a dockerized cpp service that is capable of communicating with 
other services using remote procedure calls over http, as well as messaging queues.

# What's implemented?

- gRPC for RPC communication (server and client)
- Activemq-cpp for messaging queues communication (consumer and producer)

# Build system?

CMake is used as the build system builder, building the project is pretty standard, but the build system is used in a way that 
isn't the standard way it's designed to be used, because I followed a few dogmatic beliefs of mine.

## General build process structure

The hierarchy of the build system separates building third party libraries and service source code by invoking external
project builds (ExternalProject module of CMake) to build third party libraries used in the service, while using simple
cmake files to build the various modules of the service.
 
 Normally, one cannot efficiently mix external project builds with local builds, because of a deficiency in the way
 external projects are implemented in CMake, this issue is understandable, if you know enough about the separation of
 configuration and build phases in CMake, but this unfortunate fact forces a library user who wants to import the results 
 of an external project build to use superbuilds to integrate those third party external build results into their code, 
 or suffer the loss of valuable CMake features such as find_package and sisters. This is an unacceptable practice, and 
 I refuse to follow it, luckily, CMake is flexible enough to work around this issue until a better solution is integrated
 into CMake.
 
 ## How do I build this?

Although there's a distinction between third party dependencies and service source code builds in this skeleton project,
the process of building the whole project is no different than building regular CMake based projects, 
because of some trickery in the way the build works, you simply create your build directory, cd into it, and run:

```bash
cmake -DCMAKE_BUILD_TYPE=${BUILD-TYPE} \
${path-to-cpp-service-skeleton-source} \
-DCMAKE_C_COMPILER=<path to your c compiler, eg /usr/local/bin/gcc-9> \
-DCMAKE_CXX_COMPILER=<path to your c++ compiler, eg /usr/local/bin/g++-9> \
-G "CodeBlocks - Unix Makefiles"
```
BUILD-TYPE = Release|Debug

You now have a proper Makefile in your build directory, you can now run make in that directory:

```bash
make service
```

Which will build an executable called `service` in you build directory, that's your executable like:
```bash
service <number>
```
The `<number>` is anything you want, it will be used to demo the use of a configured Maths function to demonstrate
pre-processor define based compilation.

This will take a serious amount of time (go make yourself a cup of coffee and drink it kind of serious, like 40 minutes
on a maxed out specs 2017 Macbook pro) the first time you build, because it will download the internet, and build the 
third party libraries used to support basic communication stuff, but once you've done that, you will no longer need to 
do it for subsequent builds unless you decide to do so (There's a boolean variable called FORCE_THIRD_PARTY_BUILD 
that you can set at the top of the root CMakeLists.txt file).

Examples for using both Activemq-cpp and gRPC are part of the source code.

## How do I run this?

You need to install activemq broker locally, start it, then run executable service.

## Why are you using CMake this way??

- I'd like to avoid having to treat my own code as an external project.
- I'd like to avoid having to maintain external library source code as submodules within my own codebase.
- I do not accept installing third party libraries that are really specific to my project independently, the project
is using a build system builder, it's the build system's responsibility to manage the dependencies of the project it's 
managing, not mine.
- I want the project to have the basic infrastructure to build/include it's own dependencies independent of the machine
on which it's being developed (there are exceptions here .. some dependencies are expected to be installed on the machine, 
such as openssl and some other libraries), if it works on my work computer by running a simple cmake build command,
it should work the exact same way on my home computer, that's limited to Unix of course, cause none of my machines runs 
Windows.

## What dependencies aren't included in the project?

This is not an extensive list, something might be missing here cause I'm not sure of all the dependencies that the third
party libraries I'm using here require, I'll add more whenever I find them.
for Apr:
- openssl (openssl-dev in ubuntu) (needs to be pre-installed)
- readline (needs to be pre-installed)
- zlib (no need to pre-install)
- Other stuff .. the build will fail if you miss some of the pre-requisites, but reading the logs and installing whatever
is missing isn't that hard really.

zlib, readline and openssl are required to build python 2.7.13, which is required to build Apr, zlib is used in this 
project to demo the build process of a component that is needed by a third party library,
but not directly by the project, so it's not necessary to have as a pre-installed dependency for this skeleton.
Note that building it is a pain, so in a real project, you want to have it as a pre-requisite and move on with your life

- pyenv (needs to be pre-installed, it's used to install python 2.7.13)

for Activemq-cpp:
- pkg-config (needs to be pre-installed, for demonstration, remove references from cms/CMakeLists.txt to ignore)
- libuuid (needs to be pre-installed, for demonstration, remove references from cms/CMakeLists.txt to ignore)
- openssl (needs to be pre-installed)
- readline (needs to be pre-installed)
- libcrypto (needs to be pre-installed)

# How do I add a third party dependency?

Read third_party/README.md

# How do I build a docker image?

TO BE ADDED AND DOCUMENTED (This may not happen, busy with other stuff, but I think it's simple enough :-D )
