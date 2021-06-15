#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "triangle.h"

void HelloTriangleApp::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello_Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.pEngineName = "no engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    // check for extension support
    // uint32_t extensionCount = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    // std::vector<VkExtensionProperties> extensions(extensionCount);
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    // std::cout << "available extensions:\n";
    // for (const auto& extension : extensions) {
    //     std::cout << '\t' << extension.extensionName << '\n';
    // }

    if (_enableValidationLayers && !checkValidationSupport()) {
        throw std::runtime_error("validation layers requested, but not available");
    }

    if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void HelloTriangleApp::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(_width, _height, "VulkanTriangle", nullptr, nullptr);
}

void HelloTriangleApp::initVulkan() {
    createInstance();
}

void HelloTriangleApp::mainLoop() {
    while(!glfwWindowShouldClose(_window)){
        glfwPollEvents();
    }

}

void HelloTriangleApp::cleanup() {
    vkDestroyInstance(_instance, nullptr);
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool HelloTriangleApp::checkValidationSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : _validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}