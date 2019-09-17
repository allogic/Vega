#!/usr/bin/env bash

vendor=$(pwd)/engine/vendor
mkdir -p $vendor

git clone https://github.com/Dav1dde/glad $vendor/glad
cd $vendor/glad
python -m glad --generator=c --out-path=gl

git clone https://github.com/glfw/glfw $vendor/glfw
cd $vendor/glfw
cmake .

git clone https://github.com/g-truc/glm $vendor/glm

git clone https://github.com/assimp/assimp $vendor/assimp
cd $vendor/assimp
cmake . && make -j4
