cmake_minimum_required(VERSION 3.9)

project(Vega)

enable_language(CXX)

# SETTINGS
set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(VEGA_DIR ${ROOT_DIR}/Vega)
set(SANDBOX_DIR ${ROOT_DIR}/Sandbox)

# VEGA
add_subdirectory(${VEGA_DIR})

# SANDBOX
add_subdirectory(${SANDBOX_DIR})