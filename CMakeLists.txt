cmake_minimum_required(VERSION 3.16)

project(Math)

# Include cmake_helper submodule
include("cmake/include.cmake")

# Common build settings
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

include(cmc-install)
cmc_install_root_component_config()

add_subdirectory(src)
