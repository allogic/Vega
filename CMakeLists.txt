cmake_minimum_required(VERSION 3.9)

project(vega)

enable_language(CXX)

# SETTINGS
set(CMAKE_CXX_STANDARD 17)

set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Vendor)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Vega/Source)

# BOOST
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71.0 REQUIRED COMPONENTS filesystem)

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
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/gl/include)

set(GLAD_SOURCE ${GLAD_DIR}/gl/src/glad.c)

# GLFW
set(GLFW_DIR ${VENDOR_DIR}/glfw)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(${GLFW_DIR})

# ASSIMP
set(ASSIMP_DIR ${VENDOR_DIR}/assimp)

set(BUILD_SHARED_LIBS OFF)
set(INJECT_DEBUG_POSTFIX)

add_subdirectory(${ASSIMP_DIR})

# YAML
set(YAML_DIR ${VENDOR_DIR}/yaml)

add_subdirectory(${YAML_DIR})

# VEGA
file(GLOB_RECURSE VEGA_HEADER ${SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE VEGA_SOURCE ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/Vega.cpp
        ${VEGA_SOURCE}                                          # VEGA
        ${VEGA_HEADER}                                          # VEGA
        ${IMGUI_SOURCE}                                         # IMGUI
        ${GLAD_SOURCE}                                          # GLAD
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
        PUBLIC ${Boost_INCLUDE_DIR}                             # BOOST
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${CMAKE_DL_LIBS}                                 # DLLIB
        PUBLIC glfw                                             # GLFW
        PUBLIC assimp                                           # ASSIMP
        PUBLIC yaml-cpp                                         # YAML
        PUBLIC ${Boost_LIBRARIES}                               # BOOST
        PUBLIC Boost::filesystem
        )