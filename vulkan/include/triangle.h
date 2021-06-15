#pragma once

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include <vulkan/vulkan.h>

class HelloTriangleApp {
public:
    HelloTriangleApp(uint32_t width, uint32_t height) : _width(width), _height(height) {}
    ~HelloTriangleApp(){}
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();

    bool checkValidationSupport();

    GLFWwindow* _window;
    VkInstance _instance;
    uint32_t  _width = 800;
    uint32_t _height = 600;

    std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif;

};