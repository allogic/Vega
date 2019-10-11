#!/usr/bin/env bash

vendor=$(pwd)/Vega/Vendor

rm -rf "$vendor"
mkdir -p "$vendor"

git clone --single-branch --branch master https://github.com/Dav1dde/glad "$vendor/GLAD"      # GLAD
git clone --single-branch --branch master https://github.com/glfw/glfw "$vendor/GLFW"         # GLFW
git clone --single-branch --branch master https://github.com/g-truc/glm "$vendor/GLM"         # GLM
git clone --single-branch --branch docking https://github.com/ocornut/imgui "$vendor/IMGUI"   # IMGUI (dockable experimental)
git clone --single-branch --branch master https://github.com/assimp/assimp "$vendor/ASSIMP"   # ASSIMP

cd "$vendor/GLAD" && python -m glad --generator=c --out-path=gl                               # GLAD (downloading remote files)
cmake . && cmake --build . -- -j2                                                             # VEGA