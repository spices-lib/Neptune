/**
* @file Image.h.
* @brief The Image Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Image.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"
#include "Render/Backend/Vulkan/Unit/Sampler.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::Image Class.
	* This class defines the Vulkan::Image behaves.
	*/
	class Image : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Image(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Image() override = default;

		/**
		* @brief Set Unit Handle.
		* 
		* @param[in] image Unit Handle.
		*/
		void SetImage(Unit::Image::Handle image);

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Image::Handle& Handle() const { return m_Image.GetHandle(); }

		/**
		* @brief Create Image.
		*
		* @param[in] info VkImageCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Create Image View.
		*
		* @param[in] info VkImageViewCreateInfo.
		*/
		void CreateImageView(const VkImageViewCreateInfo& info);

		/**
		* @brief Create Image Sampler.
		*
		* @param[in] info VkSamplerCreateInfo.
		*/
		void CreateSampler(VkSamplerCreateInfo& info);

		/**
		* @brief Set Image name.
		*
		* @param[in] name Image name.
		*/
		void SetName(const std::string& name) const;

		/**
		* @brief Get ImageView Unit Handle.
		*
		* @return Returns ImageView Unit Handle.
		*/
		const Unit::ImageView::Handle& GetView() const { return m_ImageView.GetHandle(); }

		/**
		* @brief Get Sampler Unit Handle.
		*
		* @return Returns Sampler Unit Handle.
		*/
		const Unit::Sampler::Handle& GetSampler() const { return m_ImageSampler.GetHandle(); }

		/**
		* @brief Get Image Format.
		*
		* @return Returns Image Format.
		*/
		const VkFormat& GetFormat() const { return m_Format; }

		/**
		* @brief Get Image Layout.
		*
		* @return Returns Image Layout.
		*/
		const VkImageLayout& GetLayout() const { return m_Layout; }

		/**
		* @brief Get Image Layer Count.
		*
		* @return Returns Image Layer Count.
		*/
		uint32_t GetLayerCount() const { return m_LayerCount; }

		/**
		* @brief Get Image Width.
		*
		* @return Returns Image Width.
		*/
		uint32_t Width() const { return m_Width; }

		/**
		* @brief Get Image Height.
		*
		* @return Returns Image Height.
		*/
		uint32_t Height() const { return m_Height; }

		/**
		* @brief Set Image Layout.
		*
		* @param[in] layout VkImageLayout.
		*/
		void SetLayout(VkImageLayout layout) { m_Layout = layout; }

		/**
		* @brief Transform Image Layout.
		*
		* @param[in] newLayout VkImageLayout.
		*/
		void TransitionLayout(VkImageLayout newLayout);

	private:

		Unit::Image     m_Image;                  // @brief This Image.
		Unit::ImageView m_ImageView;              // @brief This ImageView.
		Unit::Sampler   m_ImageSampler;           // @brief This Sampler.

		VkFormat        m_Format{};               // @brief VkFormat.
		VkImageLayout   m_Layout{};               // @brief VkImageLayout.
		uint32_t        m_LayerCount = 1;         // @brief Layer Count.

		uint32_t        m_Width{};                // @brief Width.
		uint32_t        m_Height{};               // @brief Height.

	};
}

#endif