set(SOURCE_DIR ${SANDBOX_DIR}/source)

# Sandbox
add_executable(sandbox ${SANDBOX_DIR}/sandbox.cpp)

target_include_directories(sandbox PUBLIC ${ENGINE_DIR})
target_include_directories(sandbox PUBLIC ${SOURCE_DIR})

target_link_libraries(sandbox engine)