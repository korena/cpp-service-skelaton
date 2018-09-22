#!/usr/bin/env bash

USAGE='Usage: config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}'

if [ -z "$1" ]; then
  echo "Missing CMAKE_CURRENT_BINARY_DIR (first argument)"
  echo "$USAGE"
  exit 1
fi

if [ -z "$2" ]; then
  echo "Missing Activemq-cpp_PREFIX (Second argument)"
  echo "$USAGE"
  exit 1
fi

CMAKE_CURRENT_BINARY_DIR=${1}
Activemq_cpp_PREFIX=${2}

# Deal with python setup (set to 2.7), this requires pyenv to be installed, cause it seems like the most reasonable
# python version hell manager around these days ...
eval "$(pyenv init -)"
pyenv install -s 2.7.10
export PYENV_VERSION=2.7.10

python --version

# Run buildconfig as stated in documentation
cd "${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq-cpp/activemq-cpp"

${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq\-cpp/activemq\-cpp/autogen.sh

# Now run configure with all the stuff around it ...
${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq\-cpp/activemq\-cpp/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}

exit 0
