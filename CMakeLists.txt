cmake_minimum_required(VERSION 3.9)

project(vega)

enable_language(CXX)

# SETTINGS
set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(VEGA_DIR ${ROOT_DIR}/Vega)

# VEGA
add_subdirectory(${VEGA_DIR})