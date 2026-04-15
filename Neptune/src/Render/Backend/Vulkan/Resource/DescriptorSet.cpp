/**
* @file DescriptorSet.cpp.
* @brief The DescriptorSet Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DescriptorSet.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/DescriptorPool.h"
#include "Render/Backend/Vulkan/RHI/RenderTarget.h"
#include "Buffer.h"

namespace Neptune::Vulkan {

	void DescriptorSet::AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = CreateSP<Buffer>(GetContext());
		
		buffer->CreateBuffer(info, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

		buffer->SetName("UniformBuffer");

		BufferBindingData                 data{};
		data.buffer                     = buffer;
		data.bufferInfo.buffer          = buffer->Handle();
		data.bufferInfo.offset          = 0;
		data.bufferInfo.range           = info.size;

		m_Bindings.emplace(binding.binding, BindingData{ binding, data });
	}

	void DescriptorSet::AddBinding(const VkDescriptorImageInfo& info, const VkDescriptorSetLayoutBinding& binding)
	{
		NEPTUNE_PROFILE_ZONE

		ImageBindingData data{};
		data.imageInfos.emplace_back(info);

		m_Bindings.emplace(binding.binding, BindingData{ binding, data });
	}

	void DescriptorSet::UpdateBuffer(uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = std::get<BufferBindingData>(m_Bindings[binding].data).buffer;

		buffer->WriteToBuffer(data);

		buffer->Flush();
	}

	void DescriptorSet::UpdateTexture(uint32_t binding, const RenderTarget* renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		auto& imageInfos = std::get<ImageBindingData>(m_Bindings[binding].data).imageInfos;

		imageInfos[0].imageLayout       = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfos[0].imageView         = renderTarget->GetView();
		imageInfos[0].sampler           = renderTarget->GetSampler();

		VkWriteDescriptorSet              write{};
		write.sType                     = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.dstBinding                = binding;
		write.dstSet                    = m_DescriptorSet.GetHandle();
		write.descriptorType            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		write.pImageInfo                = imageInfos.data();
		write.descriptorCount           = imageInfos.size();

		m_DescriptorSet.UpdateDescriptorSet(write);
	}

	void DescriptorSet::BuildDescriptorSet()
	{
		NEPTUNE_PROFILE_ZONE

		CreateDescriptorSetLayout();

		VkDescriptorSetAllocateInfo        allocInfo{};
		allocInfo.sType                  = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool         = GetContext().Get<IDescriptorPool>()->Handle();
		allocInfo.pSetLayouts            = &m_Layout.GetHandle();
		allocInfo.descriptorSetCount     = 1;

		m_DescriptorSet.AllocateDescriptorSet(GetContext().Get<IDevice>()->Handle(), allocInfo);

		DEBUGUTILS_SETOBJECTNAME(m_DescriptorSet, "DescriptorSet");
	}

	void DescriptorSet::UpdateDescriptorSet()
	{
		NEPTUNE_PROFILE_ZONE

		for (int i = 0; i < m_Bindings.size(); ++i)
		{
			const auto& binding = m_Bindings[i];

			VkWriteDescriptorSet              write{};
			write.sType                     = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			write.dstBinding                = i;
			write.dstSet                    = m_DescriptorSet.GetHandle();
			write.descriptorType            = binding.binding.descriptorType;

			switch (write.descriptorType)
			{
				case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
				{
					auto& imageInfos            = std::get<ImageBindingData>(binding.data).imageInfos;
					write.pImageInfo            = imageInfos.data();
					write.descriptorCount       = imageInfos.size();
					break;
				}
				case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
				case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
					write.pBufferInfo           = &std::get<BufferBindingData>(binding.data).bufferInfo;
					write.descriptorCount       = 1;
					break;
				default:
				{
					NEPTUNE_CORE_WARN("Invalid VkDescriptorType in UpdateDescriptorSet.")
					break;
				}
			}

			m_DescriptorSet.UpdateDescriptorSet(write);
		}
	}

	void DescriptorSet::CreateDescriptorSetLayout()
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<VkDescriptorSetLayoutBinding> setBindings{};
		std::vector<VkDescriptorBindingFlags> setBindingFlags{};

		for (auto& data : m_Bindings | std::views::values)
		{
			setBindings.emplace_back(data.binding);

			switch (data.binding.descriptorType)
			{
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT);
				break;
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT);
				break;
			default:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT);
				break;
			}
		}

		VkDescriptorSetLayoutBindingFlagsCreateInfo         bindingFlags{};
		bindingFlags.sType                                = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
		bindingFlags.pNext                                = nullptr;
		bindingFlags.pBindingFlags                        = setBindingFlags.data();
		bindingFlags.bindingCount                         = setBindingFlags.size();

		VkDescriptorSetLayoutCreateInfo                     layoutCreateInfo{};
		layoutCreateInfo.sType                            = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount                     = setBindings.size();
		layoutCreateInfo.pBindings                        = setBindings.data();
		layoutCreateInfo.flags                            = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT;
		layoutCreateInfo.pNext                            = &bindingFlags;

		m_Layout.CreateDescriptorSetLayout(GetContext().Get<IDevice>()->Handle(), layoutCreateInfo);

		DEBUGUTILS_SETOBJECTNAME(m_Layout, "DescriptorSetLayout");
	}
}

#endif