#include "renderer.h"
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

void Renderer::createRenderPipeline() {
    // Create Vertex- and Fragment-Shader modules
    VkShaderModule vertexShader = loadShader("shaders/vert.spv");
    VkShaderModule fragmentShader = loadShader("shaders/frag.spv");

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertexShader;
    vertShaderStageInfo.pName = "main";
    _shaderStages.push_back(vertShaderStageInfo);

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    vertShaderStageInfo.module = fragmentShader;
    vertShaderStageInfo.pName = "main";
    _shaderStages.push_back(fragShaderStageInfo);

    //Destroy Vertex- and Fragment-Shader modules
    vkDestroyShaderModule(_device, fragmentShader, nullptr);
    vkDestroyShaderModule(_device, vertexShader, nullptr);
}

VkShaderModule Renderer::loadShader(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file");
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = buffer.size();
    createInfo.pCode = reinterpret_cast<uint32_t*>(buffer.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
    return shaderModule;
}