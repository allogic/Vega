set(SOURCE_DIR ${SANDBOX_DIR}/source)

# SANDBOX
add_executable(sandbox ${SANDBOX_DIR}/Sandbox.cpp)

target_include_directories(sandbox PUBLIC ${SOURCE_DIR})
target_include_directories(sandbox PUBLIC ${ENGINE_DIR})

target_link_libraries(sandbox engine)