cmake_minimum_required(VERSION 3.14)

project(Math)

# Include cmake_helper submodule
include("cmake/include.cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
