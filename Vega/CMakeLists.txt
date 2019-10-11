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
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/gl/include)

set(GLAD_SOURCE ${GLAD_DIR}/gl/src/glad.c)

# GLFW
find_package(glfw3 3 REQUIRED)

# ASSIMP
set(ASSIMP_DIR ${VENDOR_DIR}/ASSIMP)

# VEGA
file(GLOB_RECURSE VEGA_HEADER ${SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE VEGA_SOURCE ${SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME}
        ${SOURCE_DIR}/Vega.hpp
        ${VEGA_SOURCE}
        ${VEGA_HEADER}
        ${IMGUI_SOURCE}
        ${GLAD_SOURCE}
        )

target_compile_definitions(${PROJECT_NAME}
        PUBLIC VEGA_ENABLE_DEBUG                                # VEGA
        PUBLIC VEGA_ROOT_PATH="/home/michael/Downloads/Vega/"   # VEGA
        PUBLIC VEGA_CPP_COMPILER="/usr/bin/gcc"                 # VEGA
        )

target_compile_definitions(${PROJECT_NAME}
        PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD                   # IMGUI
        PRIVATE GLM_ENABLE_EXPERIMENTAL                         # GLM
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC ${OPENGL_INCLUDE_DIR}                            # OPENGL
        PUBLIC ${GLAD_INCLUDE_DIR}                              # GLAD
        PUBLIC ${IMGUI_DIR}                                     # IMGUI
        PUBLIC ${GLM_DIR}                                       # GLM
        PUBLIC ${ASSIMP_DIR}/include                            # ASSIMP
        PUBLIC ${SOURCE_DIR}                                    # VEGA
        )

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_DL_LIBS}                                        # DLLIB
        glfw                                                    # GLFW
        stdc++fs                                                # STD (filesystem experimental)
        )