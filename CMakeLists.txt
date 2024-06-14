cmake_minimum_required(VERSION 3.5.0)
project(pxd-cubesample-test VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

################################################################################
## GLOBAL DEFINITIONS

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
endif(NOT MSVC)

set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(PXD_COMPILED_SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders/compiled)

find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)
find_program(SPIRV_OPT spirv-opt HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

################################################################################
## Submodule DEFINITIONS

set(BUILD_SHARED_LIBS OFF)

set(GLM_ENABLE_CXX_20 ON)
set(GLM_ENABLE_SIMD_AVX2 ON)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_USE_BUNDLED_GTEST OFF)

################################################################################
## Project Definitions

set(PXD_HEADER_FILES
    test_funcs.hpp

    # third party headers
    ${PXD_THIRD_PARTY_DIR}/glm/glm/glm.hpp
    ${PXD_THIRD_PARTY_DIR}/glm/glm/gtc/type_ptr.hpp
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/core.h
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/os.h
)

set(PXD_SOURCE_FILES
    main.cpp 
    test_funcs.cpp

    ${PXD_HEADER_FILES}
)

include_directories(
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt
    ${PXD_THIRD_PARTY_DIR}/glm/glm
    ${PXD_THIRD_PARTY_DIR}/benchmark/include/benchmark
)

add_subdirectory(${PXD_THIRD_PARTY_DIR}/glm)
add_subdirectory(${PXD_THIRD_PARTY_DIR}/fmt)
add_subdirectory(${PXD_THIRD_PARTY_DIR}/benchmark)

set(PXD_LIBS_TO_LINK
    glm
)

add_executable(${PROJECT_NAME} ${PXD_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PXD_LIBS_TO_LINK} fmt::fmt)

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    <random>
    ${PXD_HEADER_FILES}
)

if(GLSL_VALIDATOR)
    set(TARGET_ENV opengl)
    set(GLSL_VERSION 460)

    file(GLOB_RECURSE PXD_GLSL_FILES
        "${PXD_SHADER_DIR}/*.frag"
        "${PXD_SHADER_DIR}/*.vert"
    )

    foreach(GLSL_FILE ${PXD_GLSL_FILES})
        get_filename_component(GLSL_FILENAME ${GLSL_FILE} NAME_WE)

        set(SPIRV_FILE "${PXD_COMPILED_SHADER_DIR}/${GLSL_FILENAME}.spv")

        set(SPIRV_C_NAME "${GLSL_FILENAME}_spv")
        set(SPIRV_C_HEADER_FILE "${PXD_COMPILED_SHADER_DIR}/${SPIRV_C_NAME}.h")

        add_custom_target(
            ${GLSL_FILENAME}_SPIRV_TARGET
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL_FILE} -o ${SPIRV_FILE} -e main -t --glsl-version ${GLSL_VERSION} --enhanced-msgs --target-env ${TARGET_ENV} -I${PXD_SHADER_DIR} --spirv-val -g0
        )

        add_custom_target(
            ${GLSL_FILENAME}_SPIRV_C_TARGET
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL_FILE} -o ${SPIRV_C_HEADER_FILE} -e main -t --glsl-version ${GLSL_VERSION} --enhanced-msgs --target-env ${TARGET_ENV} -I${PXD_SHADER_DIR} --vn ${SPIRV_C_NAME} --spirv-val -g0
        )

        add_dependencies(${PROJECT_NAME} ${GLSL_FILENAME}_SPIRV_TARGET ${GLSL_FILENAME}_SPIRV_C_TARGET)

        if(SPIRV_OPT)
            set(SPIRV_OPT_NAME "${GLSL_FILENAME}_opt")
            set(SPIRV_OPT_FILE "${PXD_COMPILED_SHADER_DIR}/${SPIRV_OPT_NAME}.spv")

            add_custom_target(
                ${GLSL_FILENAME}_SPIRV_OPT_TARGET
                COMMAND ${SPIRV_OPT} ${SPIRV_FILE} -O -o ${SPIRV_OPT_FILE} --strip-debug --target-env=${TARGET_ENV}4.5 --upgrade-memory-model --remove-duplicates
            )

            add_dependencies(${PROJECT_NAME} ${GLSL_FILENAME}_SPIRV_OPT_TARGET)
        endif()
    endforeach()
endif()

################################################################################
## Benchmark Project Definitions

set(PXD_BENCHMARK_PROJECT pxd-cubesample-benchmark)

set(PXD_BENCHMARK_HEADER_FILES
    test_funcs.hpp

    # third party headers
    ${PXD_THIRD_PARTY_DIR}/glm/glm/glm.hpp
    ${PXD_THIRD_PARTY_DIR}/glm/glm/gtc/type_ptr.hpp
    ${PXD_THIRD_PARTY_DIR}/benchmark/include/benchmark/benchmark.h
)

set(PXD_BENCHMARK_SOURCE_FILES
    test_benchmark.cpp
    test_funcs.cpp

    ${PXD_BENCHMARK_HEADER_FILES}
)

add_executable(${PXD_BENCHMARK_PROJECT} ${PXD_BENCHMARK_SOURCE_FILES})

target_link_libraries(${PXD_BENCHMARK_PROJECT} PRIVATE ${PXD_LIBS_TO_LINK} benchmark::benchmark)

target_precompile_headers(
    ${PXD_BENCHMARK_PROJECT} PRIVATE
    <random>
    ${PXD_BENCHMARK_HEADER_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
