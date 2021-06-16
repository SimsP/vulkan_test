#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdlib>
#include <vector>
#include <vulkan/vulkan.h>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
};

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
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();

    void pickPhysicalDevice();

    GLFWwindow* _window;
    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    uint32_t  _width = 800;
    uint32_t _height = 600;

    std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    VkPhysicalDevice _device = VK_NULL_HANDLE;

#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif;

};