#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <vulkan/vulkan.h>

class VirtualSurface;

class Uniform {
public:
    Uniform(VirtualSurface *_master, VkDeviceSize size, VkShaderStageFlags _stages);
    ~Uniform();

    VkShaderStageFlags getStage() {return stages;}
    void *data; // Use it like a pointer to writable allocated GPU memory
    VkDescriptorBufferInfo *getBufferInfo() {return &bufferInfo;}
private:
    VirtualSurface *master;
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
    VkShaderStageFlags stages;
    VkDescriptorBufferInfo bufferInfo{};
};

#endif /* end of include guard: UNIFORM_HPP */