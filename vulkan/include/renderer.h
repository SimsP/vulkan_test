#pragma once

#include <vulkan/vulkan.h>
#include<string>
#include <vector>

#include "application.h"

class Application;
class Renderer {
public:
    Renderer(Application& app);

    ~Renderer() {
        cleanupRenderPipeline();
    }

    void drawFrame();

private:
    Application& _app;
    void createRenderPass();
    void createRenderPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void cleanupRenderPipeline();
    VkShaderModule loadShader(const std::string& fileName);

    VkDevice _device;
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

};