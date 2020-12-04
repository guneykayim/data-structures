cmake_minimum_required(VERSION 3.10)
project(data_structures VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(include)
include_directories(src) # because implementations of the template classes are here as hpp files
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
