set(SOURCE_DIR ${VEGA_DIR}/Source)
set(VENDOR_DIR ${VEGA_DIR}/Vendor)

# GLM
set(GLM_DIR ${VENDOR_DIR}/GLM)

# IMGUI
set(IMGUI_DIR ${VENDOR_DIR}/IMGUI)

file(GLOB IMGUI_SOURCE
        ${IMGUI_DIR}/*.cpp
        ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp)

# GLAD
set(GLAD_DIR ${VENDOR_DIR}/GLAD)

file(GLOB GLAD_SOURCE ${GLAD_DIR}/gl/src/glad.c)

# GLFW
set(GLFW_DIR ${VENDOR_DIR}/GLFW)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW tests")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate GLFW installation target")

add_subdirectory(${GLFW_DIR})

# ASSIMP
set(ASSIMP_DIR ${VENDOR_DIR}/ASSIMP)

# VEGA
file(GLOB_RECURSE VEGA_HEADER ${SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE VEGA_SOURCE ${SOURCE_DIR}/*.cpp)

add_library(vega ${SOURCE_DIR}/Vega.hpp
        ${VEGA_HEADER}
        ${VEGA_SOURCE}
        ${IMGUI_SOURCE}
        ${GLAD_SOURCE})

target_include_directories(vega PUBLIC ${SOURCE_DIR})
target_include_directories(vega PUBLIC ${GLM_DIR})
target_include_directories(vega PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/examples)
target_include_directories(vega PUBLIC ${GLAD_DIR}/gl/include)
target_include_directories(vega PUBLIC ${GLFW_DIR})
target_include_directories(vega PUBLIC ${ASSIMP_DIR}/include)

target_compile_definitions(vega PUBLIC VEGA_ENABLE_DEBUG)
target_compile_definitions(vega PUBLIC VEGA_ROOT_PATH="/home/michael/Downloads/Vega/")
target_compile_definitions(vega PUBLIC VEGA_CPP_COMPILER="/usr/bin/gcc")

target_compile_definitions(vega PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_compile_definitions(vega PRIVATE GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(vega glfw)
target_link_libraries(vega stdc++fs)