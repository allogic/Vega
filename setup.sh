#!/usr/bin/env bash

vendor=$(pwd)/engine/vendor

mkdir -p $vendor/glad && cd $vendor/glad
python -m glad --generator=c --out-path=gl

mkdir -p $vendor/glfw && cd $vendor/glfw
cmake .

mkdir -p $vendor/assimp && cd $vendor/assimp
cmake . && make -j4
