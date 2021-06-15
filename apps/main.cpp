#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "triangle.h"



int main(int argc, char** argv) {
    HelloTriangleApp* app = new HelloTriangleApp(800, 600);

    try {
        app->run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}