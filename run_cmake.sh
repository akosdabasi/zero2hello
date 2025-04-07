#!/bin/bash

# Define the directory containing the toolchain file
TOOLCHAIN_FILE="gcc-arm-none-eabi"

./clean_cmake.sh

# Define the build directory
BUILD_DIR="./build"

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Run cmake with the toolchain file
cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -G "Unix Makefiles"

# Optionally, you can also invoke make or another build tool after configuring
cmake --build $BUILD_DIR
