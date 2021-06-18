#pragma once

#include <vulkan/vulkan.h>
#include<string>
#include <vector>

class Renderer {
public:
    Renderer(VkDevice dev) : _device(dev) {}
    void createRenderPipeline();

private:
    VkShaderModule loadShader(const std::string& fileName);

    VkDevice _device;
    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
};