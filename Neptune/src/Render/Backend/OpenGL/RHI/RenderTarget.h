/**
* @file RenderTarget.h.
* @brief The RenderTarget Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace Neptune::OpenGL {

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
		RenderTarget(Context& context) : ContextAccessor(context) {}

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
		uint32_t GetWidth() const override { return 0; }

		/**
		* @brief Interface of Get Height.
		*
		* @return Returns height.
		*/
		uint32_t GetHeight() const override { return 0; }

	};
}

#endif