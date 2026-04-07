/**
* @file DescriptorList.h.
* @brief The DescriptorList Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Resource/DescriptorSet.h"
#include "Render/Frontend/RHI/DescriptorList.h"

#include <map>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::DescriptorList Class.
	* This class defines the Vulkan::DescriptorList behaves.
	*/
	class DescriptorList : public ContextAccessor, public RHI::RHIDescriptorList::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DescriptorList(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorList() override = default;

	public:

		/**
		* @brief Interface of Add UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] bytes UniformBuffer bytes.
		*/
		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) override;

		/**
		* @brief Interface of Add UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void AddUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget) override;

		/**
		* @brief Interface of Update UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] data UniformBuffer data.
		*/
		void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) override;

		/**
		* @brief Interface of Update UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget) override;

		/**
		* @brief Interface of Combine Shared DescriptorList.
		*
		* @param[in] shared RHIDescriptorList::Impl.
		*/
		void CombineSharedLayout(const RHI::RHIDescriptorList::Impl* shared) override;

		/**
		* @brief Interface of Build DescriptorList.
		*/
		void Build() override;

	public:

		/**
		* @brief Get DescriptorListLayout.
		* 
		* @return Returns DescriptorListLayout.
		*/
		const std::vector<VkDescriptorSetLayout>& GetLayouts() const { return m_DescriptorSetLayouts; }

		/**
		* @brief Get DescriptorList.
		*
		* @return Returns DescriptorList.
		*/
		const std::map<uint32_t, SP<DescriptorSet>>& GetSets() const { return m_DescriptorSets; }

	private:
		
		/**
		* @brief Access DescriptorList, if not exist than create one.
		*
		* @param[in] set .
		* 
		* @return Returns DescriptorSet.
		*/
		SP<DescriptorSet> AccessSet(uint32_t set);

	private:

		std::map<uint32_t, SP<DescriptorSet>> m_DescriptorSets;         // @brief Container of DescriptorSet.
		std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;      // @brief Container of VkDescriptorSetLayout.

	};
}