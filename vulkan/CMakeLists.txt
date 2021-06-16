project(triangle)
add_library(triangle src/triangle.cpp)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_include_directories(triangle PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_directories(triangle PUBLIC "$ENV{VULKAN_SDK}/Lib")
target_compile_features(triangle PUBLIC cxx_std_20)
target_link_libraries(triangle PUBLIC glfw vulkan-1)