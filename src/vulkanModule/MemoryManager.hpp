#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <vulkan/vulkan.h>
#include <list>
#include <vector>
#include <array>
#include <map>
#include "SubMemory.hpp"
#include <mutex>

class Vulkan;
class Uniform;

struct MappedMemory {
    int nbMapping = 0;
    void *data = nullptr;
};

class MemoryManager
{
public:
    MemoryManager(Vulkan *_master, uint32_t _chunkSize = 256*1024*1024);
    ~MemoryManager();
    //! Allocate memory
    //! @return SubMemory.memory can be VK_NULL_HANDLE if memory allocation has failed
    SubMemory malloc(const VkMemoryRequirements &memRequirements, VkMemoryPropertyFlags properties, VkMemoryPropertyFlags preferedProperties = 0);
    //! Release allocated memory
    void free(SubMemory &subMemory);
    //! Map memory
    void mapMemory(SubMemory &subMemory, void **data);
    //! Unmap memory
    void unmapMemory(SubMemory &subMemory);
    uint32_t getChunkSize() const {return chunkSize;}
private:
    //! Assign the memory index according to requirements
    void findMemoryIndex(const VkMemoryRequirements &memRequirements, VkMemoryPropertyFlags properties, VkMemoryPropertyFlags preferedProperties, SubMemory *subMemory);
    //! Assign the smallest compatible SubMemory
    void acquireSubMemory(const VkMemoryRequirements &memRequirements, SubMemory *subMemory);
    //! Allocate requested size and alignment inside SubMemory, releasing unused memory range(s)
    void allocateInSubMemory(const VkMemoryRequirements &memRequirements, SubMemory *subMemory);
    //! Insert SubMemory in availableSpaces of corresponding memory type
    void insert(SubMemory &subMemory);
    //! Merge with SubMemory of which the begin or the end is common
    void merge(SubMemory *subMemory);
    //! Return SubMemory which cover the whole newly allocated chunk of memory
    SubMemory allocateChunk(uint32_t memoryIndex);
    //! Write memory statistics in log
    void displayResources();
    std::mutex mtx;
    Vulkan *master;
    const VkDevice &refDevice;
    VkPhysicalDeviceMemoryProperties2 memProperties{};
    VkPhysicalDeviceMemoryBudgetPropertiesEXT memBudjet{};
    typedef struct Memory {
        std::list<SubMemory> availableSpaces;
        std::vector<VkDeviceMemory> memoryChunks;
    } Memory;
    std::array<Memory, VK_MAX_MEMORY_TYPES> memory;
    std::map<VkDeviceMemory, MappedMemory> mappedMemory;
    const uint32_t chunkSize;
};

#endif /* end of include guard: MEMORY_MANAGER_HPP */
