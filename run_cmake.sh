#!/bin/bash

build_type=${1,,:-"debug"}
echo "generating build system for $build_type"

# Define the build directory
BUILD_DIR="./build"

# Create the build directory if it doesn't exist
# mkdir -p $BUILD_DIR

# Run cmake with the appropriate preset (source dir is the current directory)
cmake --preset $build_type

# Optionally, you can also invoke make or another build tool after configuring
cmake --build --preset $build_type
