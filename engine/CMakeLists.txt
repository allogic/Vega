set(SOURCE_DIR ${ENGINE_DIR}/source)
set(VENDOR_DIR ${ENGINE_DIR}/vendor)

# GLM
set(GLM_DIR ${VENDOR_DIR}/glm)

# IMGUI
set(IMGUI_DIR ${VENDOR_DIR}/imgui)

file(GLOB IMGUI_SOURCE
        ${IMGUI_DIR}/*.cpp
        ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp)

# GLAD
set(GLAD_DIR ${VENDOR_DIR}/glad)

file(GLOB GLAD_SOURCE ${GLAD_DIR}/gl/src/glad.c)

# GLFW
set(GLFW_DIR ${VENDOR_DIR}/glfw)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW tests")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate GLFW installation target")

add_subdirectory(${GLFW_DIR})

# ASSIMP
set(ASSIMP_DIR ${VENDOR_DIR}/assimp)

# ENGINE
add_library(engine ${ENGINE_DIR}/Engine.hpp
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