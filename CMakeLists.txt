cmake_minimum_required(VERSION 3.11-3.18)

project(cmake_test VERSION 1.0 DESCRIPTION "Small CMake example built with VSCode")

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

add_subdirectory(vulkan)
add_subdirectory(apps)