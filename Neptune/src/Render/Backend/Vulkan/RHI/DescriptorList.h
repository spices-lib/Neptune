#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Resource/DescriptorSet.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include "Render/Frontend/RHI/DescriptorList.h"
#include <map>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	class DescriptorList : public ContextAccessor, public RHI::RHIDescriptorList::Impl
	{
	public:

		DescriptorList(Context& context) : ContextAccessor(context) {}
		~DescriptorList() override = default;

		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) override;

		void AddUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget) override;

		void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) override;

		void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget) override;

		void CombineSharedLayout(RHI::RHIDescriptorList::Impl* shared) override;

		void Build() override;

		const std::vector<VkDescriptorSetLayout>& GetLayouts() const { return m_DescriptorSetLayouts; }

		const std::map<uint32_t, SP<DescriptorSet>>& GetSets() const { return m_DescriptorSets; }

	private:
		
		SP<DescriptorSet> AccessSet(uint32_t set);

	private:

		std::map<uint32_t, SP<DescriptorSet>> m_DescriptorSets;
		std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;

	};
}