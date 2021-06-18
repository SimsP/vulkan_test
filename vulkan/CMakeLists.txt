project(triangle)
add_library(triangle src/triangle.cpp
                     src/renderer.cpp)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glfw3 CONFIG REQUIRED)

#find glsl->spir-v compiler
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
if(NOT glslc_executable)
    message(FATAL ERROR "GLSLC not found")
endif()

#TODO implement shader compilation
target_include_directories(triangle PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_directories(triangle PUBLIC "$ENV{VULKAN_SDK}/Lib")
target_compile_features(triangle PUBLIC cxx_std_20)
target_link_libraries(triangle PUBLIC glfw vulkan-1)