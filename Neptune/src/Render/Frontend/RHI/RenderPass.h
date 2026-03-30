/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Texture/RenderTarget.h"
#include "Render/Frontend/Utils.h"

namespace Neptune::RHI {
	
	using RHIRenderPass = RHI<ERHI::RenderPass>;

	/**
	* @brief Specialization of RHIRenderPass::Impl
	*/
	template<>
	class RHIRenderPass::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;

		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		virtual void AddSwapChainAttachment() = 0;

		/**
		* @brief Interface of Add Color Attachment.
		* 
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		virtual void AddColorAttachment(SP<class RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) = 0;

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		virtual void Build(uint32_t count) = 0;
	};

	/**
	* @brief RHI of ERHI::RenderPass
	*/
	class RenderPass : public RHIRenderPass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		RenderPass() = default;

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override = default;
		
		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		void AddSwapChainAttachment() const { RHIRenderPass::m_Impl->AddSwapChainAttachment(); }

		/**
		* @brief Interface of Add Color Attachment.
		*
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		void AddColorAttachment(SP<class RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) const { RHIRenderPass::m_Impl->AddColorAttachment(renderTarget, info); }

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		void Build(uint32_t count = MaxFrameInFlight) const { RHIRenderPass::m_Impl->Build(count); }

	};
}