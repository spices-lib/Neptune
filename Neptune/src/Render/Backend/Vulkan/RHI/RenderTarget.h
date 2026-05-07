/**
* @file RenderTarget.h.
* @brief The RenderTarget Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Resource/Image.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/Resource/DescriptorSet.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::RenderTarget Class.
	* This class defines the Vulkan::RenderTarget behaves.
	*/
	class RenderTarget : public ContextAccessor, public RHI::RHIRenderTarget::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		RenderTarget(Context& context) : ContextAccessor(context), m_DescriptorSet(context) {}

		/**
		* @brief Destructor Function.
		*/
		~RenderTarget() override = default;

	public:

		/**
		* @brief Interface of Create RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateRenderTarget(const RenderTargetCreateInfo& info) override;

		/**
		* @brief Interface of Create BindingID.
		*
		* @return Returns BindingID.
		*/
		void* CreateBindingID() override;

		/**
		* @brief Interface of Copy To RenderTarget.
		*
		* @param[in] target RenderTarget.
		*
		* @return Returns true if succeeded.
		*/
		bool CopyToRenderTarget(const RHI::RenderTarget* target) override;

		/**
		* @brief Interface of Get Format.
		*
		* @return Returns format.
		*/
		TextureFormat GetFormat() const override;

		/**
		* @brief Interface of Get Width.
		*
		* @return Returns width.
		*/
		uint32_t GetWidth() const override { return m_Image->Width(); }

		/**
		* @brief Interface of Get Height.
		*
		* @return Returns height.
		*/
		uint32_t GetHeight() const override { return m_Image->Height(); }

	public:

		/**
		* @brief Set Image.
		*
		* @return Returns image Image.
		*/
		void SetImage(SP<Resource::Image> image) { m_Image = image; }

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Image::Handle& Handle() const { return m_Image->Handle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @return Returns Unit Handle Interface.
		*/
		SP<Resource::Image> IHandle() { return m_Image; }

		/**
		* @brief Get ImageView Unit Handle.
		*
		* @return Returns ImageView Unit Handle.
		*/
		const Unit::ImageView::Handle& GetView() const { return m_Image->GetView(); }

		/**
		* @brief Get Sampler Unit Handle.
		*
		* @return Returns Sampler Unit Handle.
		*/
		const Unit::Sampler::Handle& GetSampler() const { return m_Image->GetSampler(); }

		/**
		* @brief Copy to RenderTarget.
		*
		* @param[in] target RenderTarget.
		*/
		bool CopyToRenderTarget(RenderTarget* target) const;

	private:

		/**
		* @brief Create Color RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateColorRenderTarget(const RenderTargetCreateInfo& info);

		/**
		* @brief Create Depth RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateDepthRenderTarget(const RenderTargetCreateInfo& info);

	private:

		SP<Resource::Image> m_Image;                      // @brief This Image.
		Resource::DescriptorSet m_DescriptorSet;          // @brief This DescriptorSet.
	};
}

#endif