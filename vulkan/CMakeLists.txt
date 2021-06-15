project(triangle)
add_library(triangle src/triangle.cpp)

target_include_directories(triangle PUBLIC $(PROJECT_SOURCE_DIR)/include C:/glfw-3.3.4.bin.WIN64/include C:/VulkanSDK/1.2.176.1/Include)
target_link_directories(triangle PRIVATE C:/glfw-3.3.4.bin.WIN64/lib C:/VulkanSDK/1.2.176.1/Lib)

target_compile_features(triangle PUBLIC cxx_std_20)
target_link_libraries(triangle C:/glfw-3.3.4.bin.WIN64/lib/glfw3.lib C:/VulkanSDK/1.2.176.1/Lib/vulkan-1.lib)