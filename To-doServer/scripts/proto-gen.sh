#!/bin/bash
CURRENT_DIR=$(pwd)

mkdir -p "$CURRENT_DIR/genproto"

rm -rf ./genproto/*

if [ -z "$VCPKG_ROOT" ]; then
  echo "[ERROR] VCPKG_ROOT environment variable is not set."
  exit 1
fi
if [ -z "$VCPKG_TARGET_TRIPLET" ]; then
  echo "[ERROR] VCPKG_TARGET_TRIPLET environment variable is not set."
  exit 1
fi

PROTOC="$VCPKG_ROOT/installed/$VCPKG_TARGET_TRIPLET/tools/protobuf/protoc"
GRPC_PLUGIN="$VCPKG_ROOT/installed/$VCPKG_TARGET_TRIPLET/tools/grpc/grpc_cpp_plugin"


for file in $(find $CURRENT_DIR/../protos/* ); do
    #echo $file
    #echo $CURRENT_DIR
    $PROTOC -I "$CURRENT_DIR/../protos/" \
           --cpp_out="$CURRENT_DIR/genproto/" \
           --grpc_out="$CURRENT_DIR/genproto/" \
           --plugin=protoc-gen-grpc="which grpc_cpp_plugin" \
           $file
done