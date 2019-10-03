#!/usr/bin/env bash

vendor=$(pwd)/Vega/Vendor

rm -rf $vendor
mkdir -p $vendor

# GLAD
git clone https://github.com/Dav1dde/glad $vendor/GLAD
cd $vendor/GLAD
python -m glad --generator=c --out-path=gl

# GLFW
git clone https://github.com/glfw/glfw $vendor/GLFW
cd $vendor/GLFW
cmake .

# ENTITYX
git clone https://github.com/alecthomas/entityx $vendor/ENTITYX

# GLM
git clone https://github.com/g-truc/glm $vendor/GLM

# IMGUI
git clone --single-branch --branch docking https://github.com/ocornut/imgui $vendor/IMGUI

# ASSIMP
git clone https://github.com/assimp/assimp $vendor/ASSIMP
cd $vendor/ASSIMP
cmake . && make -j4
