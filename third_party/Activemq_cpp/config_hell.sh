#!/usr/bin/env bash
set -e
set -x

USAGE="Usage: config_hell.sh ${CMAKE_CURRENT_BINARY_DIR} ${Activemq-cpp_PREFIX} ${Apr_INSTALL_PREFIX} ${local_zlib_INSTALL}"

if [[ -z "$1" ]]; then
  echo "Missing CMAKE_CURRENT_BINARY_DIR (first argument)"
  echo "$USAGE"
  exit 1
fi

if [[ -z "$2" ]]; then
  echo "Missing Activemq-cpp_PREFIX (Second argument)"
  echo "$USAGE"
  exit 1
fi

if [[ -z "$3" ]]; then
  echo "Missing Apr_INSTALL_PREFIX (Third argument)"
  echo "$USAGE"
  exit 1
fi

if [[ -z "$4" ]]; then
  echo "Missing local_zlib_INSTALL (Forth argument)"
  echo "$USAGE"
  exit 1
fi

CMAKE_CURRENT_BINARY_DIR=${1}
Activemq_cpp_PREFIX=${2}
Apr_INSTALL_PREFIX=${3}
local_zlib_INSTALL=${4}

# Deal with python setup (set to 2.7), this requires pyenv to be installed, cause it seems like the most reasonable
# python version hell manager around these days ...
eval "$(pyenv init -)"
CFLAGS="-I${local_zlib_INSTALL}/zlib/include" \
CPPFLAGS="-I${local_zlib_INSTALL}/zlib/include" \
LDFLAGS="-L${local_zlib_INSTALL}/zlib/lib" \
pyenv install --skip-existing 2.7.13
export PYENV_VERSION=2.7.13
pyenv local 2.7.13
python --version

# Run buildconfig as stated in documentation
cd "${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq-cpp/activemq-cpp"

${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq\-cpp/activemq\-cpp/autogen.sh

# Now run configure with all the stuff around it ...
${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX}/src/Activemq\-cpp/activemq\-cpp/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/${Activemq_cpp_PREFIX} \
--with-apr=${Apr_INSTALL_PREFIX}
exit 0
