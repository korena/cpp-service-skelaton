#!/usr/bin/env bash
set -e
USAGE="Usage: build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX}"

if [ -z "$1" ]; then
  echo "Missing CMAKE_CURRENT_BINARY_DIR (first argument)"
  echo "$USAGE"
  exit 1
fi

if [ -z "$2" ]; then
  echo "Missing Apr_PREFIX (Second argument)"
  echo "$USAGE"
  exit 1
fi

CMAKE_CURRENT_BINARY_DIR=${1}
Active_cpp_PREFIX=${2}

make -C "${CMAKE_CURRENT_BINARY_DIR}/${Active_cpp_PREFIX}/src/Activemq-cpp/activemq-cpp" install
exit 0
