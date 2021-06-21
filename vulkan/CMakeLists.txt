project(triangle)
add_library(triangle src/application.cpp)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
#find_package(unofficial-vulkan-memory-allocator CONFIG REQUIRED)

#find glsl->spir-v compiler
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
if(NOT glslc_executable)
    message(FATAL ERROR "GLSLC not found")
endif()

#TODO implement shader compilation
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/../apps/Debug)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/../apps/Release)
function(compile_shader target)
    cmake_parse_arguments(PARSE_ARGV 1 arg "" "ENV;FORMAT" "SOURCES")
    foreach(source ${arg_SOURCES})
        add_custom_command(
            OUTPUT ${source}.${arg_FORMAT}
           # DEPENDS ${source}
           # DEPFILE ${source}.d
            COMMAND
                ${glslc_executable}
                $<$<BOOL:${arg_ENV}>:--target-env=${arg_ENV}>
                $<$<BOOL:${arg_FORMAT}>:-mfmt=${arg_FORMAT}>
                -o ${PROJECT_BINARY_DIR}/../apps/Debug/${source}.${arg_FORMAT}
                ${PROJECT_SOURCE_DIR}/shaders/${source}
        )
        target_sources(${target} PRIVATE ${source}.${arg_FORMAT})
    endforeach()
endfunction()

compile_shader(triangle ENV vulkan FORMAT bin SOURCES shader.vert shader.frag)


target_include_directories(triangle PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_directories(triangle PUBLIC "$ENV{VULKAN_SDK}/Lib")
target_compile_features(triangle PUBLIC cxx_std_20)
target_link_libraries(triangle PUBLIC glfw vulkan-1) #unofficial::vulkan-memory-allocator::vulkan-memory-allocator)