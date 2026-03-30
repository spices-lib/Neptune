/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "DescriptorList.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/RHI/RenderTarget.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace Neptune::Vulkan {

	void DescriptorList::AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE

		auto descriptorSet = AccessSet(set);

		VkBufferCreateInfo                    info{};
		info.sType                          = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		info.size                           = bytes;
		info.usage                          = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		info.sharingMode                    = VK_SHARING_MODE_EXCLUSIVE;

		VkDescriptorSetLayoutBinding          layoutBinding{};
		layoutBinding.binding               = binding;
		layoutBinding.descriptorType        = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBinding.descriptorCount       = 1;
		layoutBinding.stageFlags            = VK_SHADER_STAGE_ALL;

		descriptorSet->AddBinding(info, layoutBinding);
	}

	void DescriptorList::AddUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		auto descriptorSet = AccessSet(set);

		VkDescriptorImageInfo                 info{};
		info.imageLayout                    = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		info.imageView                      = renderTarget->GetRHIImpl<RenderTarget>()->GetView();
		info.sampler                        = renderTarget->GetRHIImpl<RenderTarget>()->GetSampler();

		VkDescriptorSetLayoutBinding          layoutBinding{};
		layoutBinding.binding               = binding;
		layoutBinding.descriptorType        = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		layoutBinding.descriptorCount       = 1;
		layoutBinding.stageFlags            = VK_SHADER_STAGE_ALL;
		layoutBinding.pImmutableSamplers    = &renderTarget->GetRHIImpl<RenderTarget>()->GetSampler();

		descriptorSet->AddBinding(info, layoutBinding);
	}

	void DescriptorList::UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data)
	{
		NEPTUNE_PROFILE_ZONE

		m_DescriptorSets[set]->UpdateBuffer(binding, data);
	}

	void DescriptorList::UpdateUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_DescriptorSets[set]->UpdateTexture(binding, renderTarget->GetRHIImpl<RenderTarget>());
	}

	void DescriptorList::CombineSharedLayout(RHI::RHIDescriptorList::Impl* shared)
	{
		NEPTUNE_PROFILE_ZONE

		auto p = dynamic_cast<DescriptorList*>(shared);

		m_DescriptorSetLayouts.insert(m_DescriptorSetLayouts.begin(), p->GetLayouts().begin(), p->GetLayouts().end());
	}

	void DescriptorList::Build()
	{
		NEPTUNE_PROFILE_ZONE

		std::ranges::for_each(m_DescriptorSets.begin(), m_DescriptorSets.end(), [](const auto& pair) {
			
			pair.second->BuildDescriptorSet();

			pair.second->UpdateDescriptorSet();
		});

		std::ranges::for_each(m_DescriptorSets.begin(), m_DescriptorSets.end(), [&](const auto& pair) {

			m_DescriptorSetLayouts.emplace_back(pair.second->GetDescriptorSetLayout());
		});
	}

	SP<DescriptorSet> DescriptorList::AccessSet(uint32_t set)
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_DescriptorSets.contains(set))
		{
			m_DescriptorSets[set] = CreateSP<DescriptorSet>(GetContext());
		}

		return m_DescriptorSets.at(set);
	}
	
}
