set(SOURCE_DIR ${VEGA_DIR}/Source)
set(VENDOR_DIR ${VEGA_DIR}/Vendor)

# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.67 REQUIRED COMPONENTS filesystem)

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
set(GLFW_DIR ${VENDOR_DIR}/GLFW)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(${GLFW_DIR})

# ASSIMP
set(ASSIMP_DIR ${VENDOR_DIR}/ASSIMP)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(INJECT_DEBUG_POSTFIX)

add_subdirectory(${ASSIMP_DIR})

# YAML
set(YAML_DIR ${VENDOR_DIR}/YAML)

add_subdirectory(${YAML_DIR})

# VEGA
file(GLOB_RECURSE VEGA_HEADER ${SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE VEGA_SOURCE ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}
        ${SOURCE_DIR}/Vega.cpp
        ${VEGA_SOURCE}
        ${VEGA_HEADER}
        ${IMGUI_SOURCE}
        ${GLAD_SOURCE}
        )

target_compile_definitions(${PROJECT_NAME}
        PUBLIC VEGA_ENABLE_DEBUG                                # VEGA
        )

target_compile_definitions(${PROJECT_NAME}
        PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD                   # IMGUI
        PRIVATE GLM_ENABLE_EXPERIMENTAL                         # GLM
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC ${OPENGL_INCLUDE_DIR}                            # OPENGL
        PUBLIC ${GLAD_INCLUDE_DIR}                              # GLAD
        PUBLIC ${GLFW_DIR}                                      # GLFW
        PUBLIC ${IMGUI_DIR}                                     # IMGUI
        PUBLIC ${GLM_DIR}                                       # GLM
        PUBLIC ${ASSIMP_DIR}/include                            # ASSIMP
        PUBLIC ${SOURCE_DIR}                                    # VEGA
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${CMAKE_DL_LIBS}                                 # DLLIB
        PUBLIC glfw                                             # GLFW
        PUBLIC assimp                                           # ASSIMP
        PUBLIC yaml-cpp                                         # YAML
        PUBLIC Boost::filesystem                                # BOOST
        )