/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Unit/FrameBuffer.h"
#include "Device/Graphics/Backend/OpenGL/Unit/RenderBuffer.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::OpenGL {

	/**
	* @brief OpenGL::RenderPass Class.
	* This class defines the OpenGL::RenderPass behaves.
	*/
	class RenderPass : public ContextAccessor, public RHI::RHIRenderPass::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override = default;

	public:

		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		void AddSwapChainAttachment() override;

		/**
		* @brief Interface of Add Color Attachment.
		*
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		void AddColorAttachment(SP<RHI::RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) override;

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		void Build(uint32_t count = MaxFrameInFlight) override;

	private:

		std::vector<SP<Unit::FrameBuffer>>                m_FrameBuffers;                    // @brief Container of FrameBuffer.
		std::vector<SP<Unit::RenderBuffer>>               m_RenderBuffers;                   // @brief Container of RenderBuffer.

	};
}

#endif