cmake_minimum_required(VERSION 3.13)

project(vega)

enable_language(CXX)

# SETTINGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 14)

set(VEGA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(ENGINE_DIR ${VEGA_DIR}/engine)
set(SANDBOX_DIR ${VEGA_DIR}/sandbox)

# ENGINE
add_subdirectory(${ENGINE_DIR})

# SANDBOX
add_subdirectory(${SANDBOX_DIR})