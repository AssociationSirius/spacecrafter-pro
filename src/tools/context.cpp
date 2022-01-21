#include "context.hpp"
#include "draw_helper.hpp"
#include "EntityCore/EntityCore.hpp"
#include "EntityCore/Core/RenderMgr.hpp"
#include "EntityCore/Resource/SetMgr.hpp"

Context::Context()
{
    instance = this;
}

Context::~Context()
{
    instance = nullptr;
    helper.reset();
    for (auto &f : fences)
        vkDestroyFence(VulkanMgr::instance->refDevice, f, nullptr);
    for (auto &f : debugFences)
        vkDestroyFence(VulkanMgr::instance->refDevice, f, nullptr);
    for (auto &s : semaphores)
        vkDestroySemaphore(VulkanMgr::instance->refDevice, s, nullptr);
    vkDestroyCommandPool(VulkanMgr::instance->refDevice, cmdPool, nullptr);
    for (auto p : pipelineArray)
        delete[] p;
}
