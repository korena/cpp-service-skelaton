#!/usr/bin/env bash
set -e
USAGE="Usage: config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Apr-util_PREFIX}"

if [[ -z "$1" ]]; then
  echo "Missing CMAKE_CURRENT_BINARY_DIR (first argument)"
  echo "$USAGE"
  exit 1
fi

if [[ -z "$2" ]]; then
  echo "Missing Apr_PREFIX (Second argument)"
  echo "$USAGE"
  exit 1
fi

CMAKE_CURRENT_BINARY_DIR=${1}
Apr_util_PREFIX=${2}

# Deal with python setup (set to 2.7), this requires pyenv to be installed, cause it seems like the most reasonable
# python version hell manager around these days ...
eval "$(pyenv init -)"
pyenv install -s 2.7.13
export PYENV_VERSION=2.7.13

python --version

# Run buildconfig as stated in documentation
cd "${CMAKE_CURRENT_BINARY_DIR}/${Apr_util_PREFIX}/src/Apr-util"

${CMAKE_CURRENT_BINARY_DIR}/${Apr_util_PREFIX}/src/Apr\-util/buildconf

# Now run configure with all the stuff around it ...
CC="gcc -m64" ${CMAKE_CURRENT_BINARY_DIR}/${Apr_util_PREFIX}/src/Apr\-util/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/${Apr_util_PREFIX}

exit 0
