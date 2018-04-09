#!/usr/bin/env bash

DEPS_PREFIX=$1

if [ "X${DEPS_PREFIX}" == "X" ]; then
  echo "Usage: $0 third_party_dir"
  exit -1
fi

echo "THIRDPARTY=${DEPS_PREFIX}" > depends.mk
echo "BOOST_HEADER_DIR=${DEPS_PREFIX}/boost/include" >> depends.mk
echo "PROTOBUF_DIR=${DEPS_PREFIX}/protobuf" >> depends.mk
echo "SNAPPY_DIR=${DEPS_PREFIX}/snappy" >> depends.mk
echo "ZLIB_DIR=${DEPS_PREFIX}/zlib" >> depends.mk
echo "GLOG_DIR=${DEPS_PREFIX}/glog" >> depends.mk


make clean
for x in $(ls src/sofa/pbrpc/*.proto); do
  ${DEPS_PREFIX}/protobuf/bin/protoc --proto_path=./src --proto_path=${DEPS_PREFIX}/protobuf/include --cpp_out=./src $x
done

make
