#!/usr/bin/env bash

vendor=$(pwd)/Vega/Vendor

# BOOST
#if [ -d "/tmp/boost" ]; then
#  rm -rf "/tmp/boost"
#fi

#mkdir "/tmp/boost" && cd "/tmp/boost" || exit

#git clone --single-branch --branch master --recursive https://github.com/boostorg/build .
#./bootstrap.sh
#./b2 --build-dir=. --toolset=gcc --build-type=complete stage

# VENDOR

rm -rf "$vendor" && mkdir -p "$vendor" && cd "$vendor" || exit

git clone --single-branch --branch master https://github.com/Dav1dde/glad
git clone --single-branch --branch master https://github.com/glfw/glfw
git clone --single-branch --branch master https://github.com/g-truc/glm
git clone --single-branch --branch docking https://github.com/ocornut/imgui
git clone --single-branch --branch master https://github.com/assimp/assimp
git clone --single-branch --branch master https://github.com/jbeder/yaml-cpp yaml

cd "$vendor/glad" && python -m glad --generator=c --out-path=gl
