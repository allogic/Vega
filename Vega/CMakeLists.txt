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

# ENGINE
add_library(engine ${SOURCE_DIR}/Engine.hpp
        ${IMGUI_SOURCE}
        ${GLAD_SOURCE})

target_include_directories(engine PUBLIC ${SOURCE_DIR})
target_include_directories(engine PUBLIC ${GLM_DIR})
target_include_directories(engine PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/examples)
target_include_directories(engine PUBLIC ${GLAD_DIR}/gl/include)
target_include_directories(engine PUBLIC ${GLFW_DIR})
target_include_directories(engine PUBLIC ${ASSIMP_DIR}/include)

target_compile_definitions(engine PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(engine glfw)