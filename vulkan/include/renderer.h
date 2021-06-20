#pragma once

#include <vulkan/vulkan.h>
#include<string>
#include <vector>

class Renderer {
public:
    Renderer(VkDevice dev, VkExtent2D extent, VkFormat swapChainFormat, std::vector<VkImageView> imageViews)
             : _device(dev) {
        _viewport.x = 0.0f;
        _viewport.y = 0.0f;
        _viewport.width = static_cast<float>(extent.width);
        _viewport.height = static_cast<float>(extent.height);
        _viewport.minDepth = 0.0f;
        _viewport.maxDepth = 1.0f;

        _scissor.offset = {0, 0};
        _scissor.extent = extent;

        createRenderPass(swapChainFormat);
        createRenderPipeline();
        createFramebuffers(imageViews, extent);
    }

    ~Renderer() {
        cleanupRenderPipeline();
    }

private:
    void createRenderPass(VkFormat swapChainFormat);
    void createRenderPipeline();
    void createFramebuffers(std::vector<VkImageView> imageViews, VkExtent2D extent);
    void cleanupRenderPipeline();
    VkShaderModule loadShader(const std::string& fileName);

    VkDevice _device;
    VkViewport _viewport;
    VkRect2D _scissor {};
    VkRenderPass _renderPass;
    VkPipelineLayout _pipelineLayout;
    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

    VkPipeline _renderPipeline;
    std::vector<VkFramebuffer> _swapChainFramebuffers;
};