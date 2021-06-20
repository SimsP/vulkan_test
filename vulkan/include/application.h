#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdlib>
#include <vector>
#include <vulkan/vulkan.h>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Application {
public:
    Application(uint32_t width, uint32_t height) : _width(width), _height(height) {}
    ~Application(){}
    
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    bool _frameBufferResized = false;

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
    bool checkSuitableDevices(VkPhysicalDevice device);
    bool checkDeviceExtensionsSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    void createLogicalDevice();

    void createSurface();

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentationMode(const std::vector<VkPresentModeKHR>& availableModes);
    VkExtent2D chooseSwapExt(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    void recreateSwapChain();
    void cleanupSwapChain();
    void createImageViews();

    void createRenderPass();
    void createRenderPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    VkShaderModule loadShader(const std::string& fileName);

    void drawFrame();
    VkViewport _viewport;
    VkRect2D _scissor {};
    VkRenderPass _renderPass;
    VkPipelineLayout _pipelineLayout;

    VkPipeline _renderPipeline;
    std::vector<VkFramebuffer> _swapChainFramebuffers;

    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;

    std::vector<VkSemaphore> _imgAvailableSem;
    std::vector<VkSemaphore> _renderFinishedSem;
    std::vector<VkFence> _inFlightFence;
    std::vector<VkFence> _imgsInFlight;
    const int _max_frames_in_flight = 2;
    size_t _currentFrame = 0;

    GLFWwindow* _window;
    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    uint32_t  _width = 800;
    uint32_t _height = 600;

    std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> _deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
    VkDevice _device;
    VkQueue _graphicsQueue;
    VkQueue _presentQueue;

    VkSurfaceKHR _surface;
    VkSwapchainKHR _swapChain;
    std::vector<VkImage> _swapChainImages;
    VkExtent2D _swapChainExtent;
    VkFormat _swapChainImageFormat;

    std::vector<VkImageView> _swapChainImageViews;

#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif;

};