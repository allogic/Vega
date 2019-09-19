cmake_minimum_required(VERSION 3.13)

project(vega)

# Settings
set(CMAKE_CXX_STANDARD 17)

set(VEGA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(ENGINE_DIR ${VEGA_DIR}/engine)
set(SANDBOX_DIR ${VEGA_DIR}/sandbox)

# Engine
add_subdirectory(${ENGINE_DIR})

# Sandbox
add_subdirectory(${SANDBOX_DIR})