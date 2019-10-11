set(SOURCE_DIR ${SANDBOX_DIR}/Source)

# SANDBOX
file(GLOB_RECURSE SANDBOX_HEADER ${SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SANDBOX_SOURCE ${SOURCE_DIR}/*.cpp)

add_executable(sandbox ${SOURCE_DIR}/Sandbox.cpp
        ${SANDBOX_HEADER}
        ${SANDBOX_SOURCE})

target_include_directories(sandbox
        PUBLIC ${VEGA_DIR}                                          # VEGA
        PUBLIC ${SOURCE_DIR}                                        # SANDBOX
        )

target_link_libraries(sandbox
        vega                                                        # VEGA
        )