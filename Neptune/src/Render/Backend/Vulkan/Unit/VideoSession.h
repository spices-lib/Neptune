#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <array>
#include <vector>

namespace Neptune::Vulkan::Unit {

	constexpr uint32_t MAX_BOUND_MEMORY = 16;

	class VideoSession : public Unit<VkVideoSessionKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		VideoSession() : Unit() {}

		~VideoSession() override;

		void SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy, PFN_vkBindVideoSessionMemoryKHR bind);

		void CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo);

		const VkDeviceMemory& AllocateMemory(const VkMemoryAllocateInfo& info);

		void BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const;

	private:

		VkDevice                              m_Device = nullptr;
		std::vector<VkDeviceMemory>           m_Memories{};
		PFN_vkCreateVideoSessionKHR           vkCreateVideoSessionKHR = nullptr;
		PFN_vkDestroyVideoSessionKHR          vkDestroyVideoSessionKHR = nullptr;
		PFN_vkBindVideoSessionMemoryKHR       vkBindVideoSessionMemoryKHR = nullptr;
	};
}