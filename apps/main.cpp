#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include "application.h"



int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <model_path>  <texture_path>";
        return EXIT_FAILURE;
    }
    std::string model_path(argv[1]);
    std::string texture_path(argv[2]);
    

    Application* app = new Application(1280, 720, model_path, texture_path);

    try {
        app->run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}