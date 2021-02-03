cmake_minimum_required(VERSION 3.15)

project(effective_lru_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Turn on build for tests" ON)
option(BUILD_BENCHMARK "Turn on build for benchmark" ON)

find_package(benchmark REQUIRED)

file(GLOB SRC_FILES
        "src/*.cpp"
)

set(INC_FILES_DIR
        include/
)

if (BUILD_TESTS)
    #add_subdirectory(external/googletest)
    add_subdirectory(test)
endif()

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

include_directories(
        ${INC_FILES_DIR}
)

add_executable(effective_lru_cpp
        ${SRC_FILES}
)

add_library(effective_lru-static STATIC
    ${SRC_FILES})
