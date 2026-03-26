#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSet.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSetLayout.h"
#include <map>
#include <vector>
#include <variant>

namespace Neptune::Vulkan {

	class DescriptorSet : public ContextAccessor
	{
	public:

		DescriptorSet(Context& context) : ContextAccessor(context) {}
		~DescriptorSet() override = default;

		const Unit::DescriptorSet::Handle& Handle() const { return m_DescriptorSet.GetHandle(); }

		void AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding);

		void AddBinding(const VkDescriptorImageInfo& info, const VkDescriptorSetLayoutBinding& binding);

		void UpdateBuffer(uint32_t binding, void* data);

		void UpdateTexture(uint32_t binding, SP<class RenderTarget> renderTarget);

		void BuildDescriptorSet();

		void UpdateDescriptorSet();

		const Unit::DescriptorSetLayout::Handle& GetDescriptorSetLayout() const { return m_Layout.GetHandle(); }

	private:

		void CreateDescriptorSetLayout();

	private:

		struct BufferBindingData {
			SP<class Buffer> buffer;
			VkDescriptorBufferInfo bufferInfo;
		};

		struct ImageBindingData {
			std::vector<VkDescriptorImageInfo> imageInfos;
		};

		struct BindingData {
			VkDescriptorSetLayoutBinding  binding;
			std::variant<BufferBindingData, ImageBindingData> data;
		};

		Unit::DescriptorSet                       m_DescriptorSet;
		Unit::DescriptorSetLayout                 m_Layout;
		std::map<uint32_t, BindingData>           m_Bindings;
	};
}