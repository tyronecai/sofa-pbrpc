#!/usr/bin/env bash

DEPS_PREFIX=$1

echo "THIRDPARTY=${DEPS_PREFIX}" > depends.mk
echo "BOOST_HEADER_DIR=${DEPS_PREFIX}/boost/include" >> depends.mk
echo "PROTOBUF_DIR=${DEPS_PREFIX}/protobuf" >> depends.mk
echo "SNAPPY_DIR=${DEPS_PREFIX}/snappy" >> depends.mk
echo "ZLIB_DIR=${DEPS_PREFIX}/zlib" >> depends.mk
echo "GLOG_DIR=${DEPS_PREFIX}/glog" >> depends.mk

make
