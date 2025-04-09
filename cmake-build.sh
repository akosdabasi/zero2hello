#!/bin/bash

build_type=${1:-"debug"}
build_type=${build_type,,}
echo "build $build_type configuration"

# Optionally, you can also invoke make or another build tool after configuring
cmake --build --preset $build_type