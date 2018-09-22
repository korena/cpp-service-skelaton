#!/usr/bin/env bash

USAGE='Usage: build_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr-util_PREFIX}'

if [ -z "$1" ]; then
  echo "Missing CMAKE_CURRENT_BINARY_DIR (first argument)"
  echo "$USAGE"
  exit 1
fi

if [ -z "$2" ]; then
  echo "Missing Apr-util_PREFIX (Second argument)"
  echo "$USAGE"
  exit 1
fi

CMAKE_CURRENT_BINARY_DIR=${1}
Apr_util_PREFIX=${2}

make -C "${CMAKE_CURRENT_BINARY_DIR}/${Apr_util_PREFIX}/src/Apr-util" install
exit 0
