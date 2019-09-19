set(SOURCE_DIR ${ENGINE_DIR}/source)
set(VENDOR_DIR ${ENGINE_DIR}/vendor)

# Engine
add_library(engine ${ENGINE_DIR}/Engine.h)

target_include_directories(engine PUBLIC ${SOURCE_DIR})

set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

# GLAD
set(GLAD_DIR ${VENDOR_DIR}/glad)

add_library(glad ${GLAD_DIR}/gl/src/glad.c)

target_include_directories(glad PRIVATE ${GLAD_DIR}/gl/include)
target_include_directories(engine PUBLIC ${GLAD_DIR}/gl/include)

target_link_libraries(engine glad ${CMAKE_DL_LIBS})

# GLFW
set(GLFW_DIR ${VENDOR_DIR}/glfw)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW tests")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate GLFW installation target")

add_subdirectory(${GLFW_DIR})

target_include_directories(engine PUBLIC ${GLFW_DIR}/include)

target_link_libraries(engine glfw ${GLFW_LIBRARIES})

target_compile_definitions(engine PRIVATE GLFW_INCLUDE_NONE)

# GLM
set(GLM_DIR ${VENDOR_DIR}/glm)

target_include_directories(engine PUBLIC ${GLM_DIR})

# Assimp
set(ASSIMP_DIR ${VENDOR_DIR}/assimp)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "Build the ASSIMP tools")
set(INJECT_DEBUG_POSTFIX OFF CACHE INTERNAL "Inject ASSIMP debug postfix")
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "Build the ASSIMP tests")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build the ASSIMP shared libraries")

target_include_directories(engine PUBLIC ${ASSIMP_DIR}/include)