#ifndef PIPELINE_LAYOUT_HPP
#define PIPELINE_LAYOUT_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <list>
#include <array>

class VirtualSurface;
class Uniform;

class PipelineLayout {
public:
    PipelineLayout(VirtualSurface *_master);
    ~PipelineLayout();
    //! @brief Set uniform location to this PipelineLayout
    //! @param stages combination of flags describing the types of shader accessing it (vertex, fragment, etc.)
    void setUniformLocation(VkShaderStageFlags stage, uint32_t binding, uint32_t arraySize = 1, bool isVirtual = false);
    void setTextureLocation(uint32_t binding, const VkSamplerCreateInfo *samplerInfo = nullptr, VkShaderStageFlags stage = VK_SHADER_STAGE_FRAGMENT_BIT);
    void setPushConstant(VkShaderStageFlags stage, uint32_t offset, uint32_t size);
    //! Build pipelineLayout
    void build();
    //! Build set emplacement
    void buildLayout(VkDescriptorSetLayoutCreateFlags flags = 0);
    //! Link to global pipelineLayout in parameter
    void setGlobalPipelineLayout(PipelineLayout *pl);
    VkPipelineLayout &getPipelineLayout() {return pipelineLayout;}
    VkDescriptorSetLayout &getDescriptorLayout(int index = -1) {return descriptor[(index != -1) ? index : descriptorPos.front()];}
    static VkSamplerCreateInfo DEFAULT_SAMPLER;

private:
    VirtualSurface *master;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    bool isOk = true;
    std::vector<VkDescriptorSetLayoutBinding> uniformsLayout;
    std::vector<VkDescriptorSetLayout> descriptor;
    std::vector<VkPushConstantRange> pushConstants;
    std::list<VkSampler> sampler;
    //! Inform which descriptor is owned by this PipelineLayout
    std::vector<int> descriptorPos;

    bool builded = false;
};

#endif /* end of include guard: PIPELINE_LAYOUT_HPP */
