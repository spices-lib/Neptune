#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Image.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"
#include "Render/Backend/Vulkan/Unit/Sampler.h"

namespace Neptune::Vulkan {

	class Image : public ContextAccessor
	{
	public:

		Image(Context& context) : ContextAccessor(context) {}
		~Image() override = default;

		void SetImage(VkImage image);

		const Unit::Image::Handle& Handle() const { return m_Image.GetHandle(); }

		void CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

		void CreateImageView(const VkImageViewCreateInfo& info);

		void CreateSampler(VkSamplerCreateInfo& info);

		void SetName(const std::string& name) const;

		const Unit::ImageView::Handle& GetView() const { return m_ImageView.GetHandle(); }

		const Unit::Sampler::Handle& GetSampler() const { return m_ImageSampler.GetHandle(); }

		const VkFormat& GetFormat() const { return m_Format; }

		const VkImageLayout& GetLayout() const { return m_Layout; }

		uint32_t GetLayerCount() const { return m_LayerCount; }

		uint32_t Width() const { return m_Width; }

		uint32_t Height() const { return m_Height; }

		void SetLayout(VkImageLayout layout) { m_Layout = layout; }

		void TransitionLayout(VkImageLayout newLayout);

	private:

		Unit::Image     m_Image;
		Unit::ImageView m_ImageView;
		Unit::Sampler   m_ImageSampler;

		VkFormat        m_Format;
		VkImageLayout   m_Layout;
		uint32_t        m_LayerCount = 1;

		uint32_t        m_Width;
		uint32_t        m_Height;
	};
}