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

set(PXD_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(PXD_COMPILED_SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders/compiled)

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
    ${PXD_SOURCES_DIR}/test_funcs.hpp

    # third party headers
    ${PXD_THIRD_PARTY_DIR}/glm/glm/glm.hpp
    ${PXD_THIRD_PARTY_DIR}/glm/glm/gtc/type_ptr.hpp
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/core.h
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/os.h
)

set(PXD_SOURCE_FILES
    main.cpp 
    ${PXD_SOURCES_DIR}/test_funcs.cpp

    ${PXD_HEADER_FILES}
)

include_directories(
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt
    ${PXD_THIRD_PARTY_DIR}/glm/glm
    ${PXD_THIRD_PARTY_DIR}/benchmark/include/benchmark
    ${PXD_THIRD_PARTY_DIR}/glfw/include/GLFW
    ${PXD_COMPILED_SHADER_DIR}
    ${PXD_SOURCES_DIR}
)

add_subdirectory(${PXD_THIRD_PARTY_DIR}/glm)
add_subdirectory(${PXD_THIRD_PARTY_DIR}/fmt)
add_subdirectory(${PXD_THIRD_PARTY_DIR}/benchmark)
add_subdirectory(${PXD_THIRD_PARTY_DIR}/glfw)

add_executable(${PROJECT_NAME} ${PXD_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE glm fmt::fmt)

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    <random>
    ${PXD_HEADER_FILES}
)

################################################################################
## OpenGL ES Test Project Definitions

set(PXD_GRAPHIC_TEST_PROJECT pxd-cubesample-opengles)

include(CompileShaders.cmake)

compile_glsl_shaders(
    ${PROJECT_NAME} 
    opengl 
    opengl4.5 
    ${PXD_SHADER_DIR} 
    ${PXD_COMPILED_SHADER_DIR} 
    ${PXD_COMPILED_SHADER_DIR}
)

set(PXD_GRAPHIC_TEST_HEADER_FILES
    ${PXD_SOURCES_DIR}/test_funcs.hpp
    ${PXD_SOURCES_DIR}/gles_funcs.hpp
    ${PXD_COMPILED_SHADER_DIR}/temp_vert_spv.h

    # third party headers
    ${PXD_THIRD_PARTY_DIR}/glm/glm/glm.hpp
    ${PXD_THIRD_PARTY_DIR}/glm/glm/gtc/type_ptr.hpp
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/core.h
    ${PXD_THIRD_PARTY_DIR}/fmt/include/fmt/os.h
    ${PXD_THIRD_PARTY_DIR}/glfw/include/GLFW/glfw3.h
    ${PXD_SOURCES_DIR}/gles2.h
)

set(PXD_GRAPHIC_TEST_SOURCE_FILES
    ${PXD_SOURCES_DIR}/gles_funcs.cpp
    ${PXD_SOURCES_DIR}/test_opengles.cpp 
    ${PXD_SOURCES_DIR}/test_funcs.cpp

    ${PXD_HEADER_FILES}
)

add_executable(${PXD_GRAPHIC_TEST_PROJECT} ${PXD_GRAPHIC_TEST_SOURCE_FILES})

target_link_libraries(${PXD_GRAPHIC_TEST_PROJECT} PRIVATE glm fmt::fmt glfw)

target_precompile_headers(
    ${PXD_GRAPHIC_TEST_PROJECT} PRIVATE
    <random>
    ${PXD_GRAPHIC_TEST_HEADER_FILES}
)

################################################################################
## Benchmark Project Definitions

set(PXD_BENCHMARK_PROJECT pxd-cubesample-benchmark)

set(PXD_BENCHMARK_HEADER_FILES
    ${PXD_SOURCES_DIR}/test_funcs.hpp

    # third party headers
    ${PXD_THIRD_PARTY_DIR}/glm/glm/glm.hpp
    ${PXD_THIRD_PARTY_DIR}/glm/glm/gtc/type_ptr.hpp
    ${PXD_THIRD_PARTY_DIR}/benchmark/include/benchmark/benchmark.h
)

set(PXD_BENCHMARK_SOURCE_FILES
    ${PXD_SOURCES_DIR}/test_benchmark.cpp
    ${PXD_SOURCES_DIR}/test_funcs.cpp

    ${PXD_BENCHMARK_HEADER_FILES}
)

add_executable(${PXD_BENCHMARK_PROJECT} ${PXD_BENCHMARK_SOURCE_FILES})

target_link_libraries(${PXD_BENCHMARK_PROJECT} PRIVATE glm benchmark::benchmark)

target_precompile_headers(
    ${PXD_BENCHMARK_PROJECT} PRIVATE
    <random>
    ${PXD_BENCHMARK_HEADER_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
