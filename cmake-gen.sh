#!/bin/bash

build_type=${1:-"debug"}
build_type=${build_type,,}
echo "generating build system for $build_type configuration"

# Run cmake with the appropriate preset (source dir is the current directory)
cmake --preset $build_type

