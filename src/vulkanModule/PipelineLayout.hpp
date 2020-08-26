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
    void setUniformLocation(VkShaderStageFlags stage, uint32_t binding, uint32_t arraySize = 1);
    void setTextureLocation(uint32_t binding, const VkSamplerCreateInfo *samplerInfo = nullptr);
    void pushConstant(); // set constant values
    //! Build pipelineLayout
    void build();
    //! Build as global pipelineLayout
    void buildLayout();
    //! Link to global pipelineLayout in parameter
    void setGlobalPipelineLayout(PipelineLayout *pl);
    VkPipelineLayout &getPipelineLayout() {return pipelineLayout;}
    VkDescriptorSetLayout &getDescriptorLayout() {return descriptor[0];}
    static VkSamplerCreateInfo DEFAULT_SAMPLER;
private:
    VirtualSurface *master;
    VkPipelineLayout pipelineLayout;
    std::vector<VkDescriptorSetLayoutBinding> uniformsLayout;
    std::array<VkDescriptorSetLayout, 2> descriptor;
    std::list<VkSampler> sampler;

    bool builded = false;
};

#endif /* end of include guard: PIPELINE_LAYOUT_HPP */