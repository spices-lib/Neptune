/**
* @file DecodePictureBuffer.h.
* @brief The DecodePictureBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSet.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSetLayout.h"

#include <map>
#include <vector>
#include <variant>

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::DescriptorSet Class.
	* This class defines the Vulkan::DescriptorSet behaves.
	*/
	class DescriptorSet : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DescriptorSet(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorSet() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::DescriptorSet::Handle& Handle() const { return m_DescriptorSet.GetHandle(); }

		/**
		* @brief Add DescriptorSet Binding.
		*
		* @param[in] info VkBufferCreateInfo.
		* @param[in] binding VkDescriptorSetLayoutBinding.
		*/
		void AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding);

		/**
		* @brief Add DescriptorSet Binding.
		*
		* @param[in] info VkDescriptorImageInfo.
		* @param[in] binding VkDescriptorSetLayoutBinding.
		*/
		void AddBinding(const VkDescriptorImageInfo& info, const VkDescriptorSetLayoutBinding& binding);

		/**
		* @brief Update Buffer Binding.
		*
		* @param[in] binding .
		* @param[in] data Buffer Data.
		*/
		void UpdateBuffer(uint32_t binding, const void* data);

		/**
		* @brief Update Texture Binding.
		*
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateTexture(uint32_t binding, const class RenderTarget* renderTarget);

		/**
		* @brief Build DescriptorSet.
		*/
		void BuildDescriptorSet();

		/**
		* @brief Update DescriptorSet.
		*/
		void UpdateDescriptorSet();

		/**
		* @brief Get DescriptorSetLayout Unit Handle.
		*
		* @return Returns DescriptorSetLayout Unit Handle.
		*/
		const Unit::DescriptorSetLayout::Handle& GetDescriptorSetLayout() const { return m_Layout.GetHandle(); }

	private:

		/**
		* @brief Create DescriptorSetLayout.
		*/
		void CreateDescriptorSetLayout();

	private:

		/**
		* @brief Buffer Binding Data
		*/
		struct BufferBindingData 
		{
			SP<class Buffer> buffer;                                    // @brief Buffer Reference.
			VkDescriptorBufferInfo bufferInfo;                          // @brief VkDescriptorBufferInfo.
		};										                       

		/**
		* @brief Image Binding Data
		*/
		struct ImageBindingData 
		{
			std::vector<VkDescriptorImageInfo> imageInfos;              // @brief VkDescriptorImageInfo.
		};

		/**
		* @brief Binding Data
		*/
		struct BindingData 
		{
			VkDescriptorSetLayoutBinding  binding;                      // @brief VkDescriptorSetLayoutBinding.
			std::variant<BufferBindingData, ImageBindingData> data;     // @brief Specific Binding.
		};

		Unit::DescriptorSet                       m_DescriptorSet;      // @brief This DescriptorSet.
		Unit::DescriptorSetLayout                 m_Layout;             // @brief This DescriptorSetLayout.
		std::map<uint32_t, BindingData>           m_Bindings;           // @brief This Binding.
	};
}