/**
* @file OpticalFlowSession.h.
* @brief The OpticalFlowSession Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/OpticalFlowSession.h"
#include "Render/Frontend/RHI/OpticalFlow.h"

#include <unordered_map>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::OpticalFlowSession Class.
	* This class defines the Vulkan::OpticalFlowSession behaves.
	*/
	class OpticalFlowSession : public ContextAccessor, public RHI::RHIOpticalFlow::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit OpticalFlowSession(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~OpticalFlowSession() override = default;

	public:

		/**
		* @brief Interface of Set Input RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetInputRenderTarget(SP<RHI::RenderTarget> rt) override;

		/**
		* @brief Interface of Set Reference RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetReferenceRenderTarget(SP<RHI::RenderTarget> rt) override;

		/**
		* @brief Interface of Set FlowVector RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetFlowVectorRenderTarget(SP<RHI::RenderTarget> rt) override;

		/**
		* @brief Interface of Create OpticalFlow Session.
		*
		* @retrun Returns true if succeeded.
		*/
		bool CreateOpticalFlowSession() override;

		/**
		* @brief Interface of OpticalFlow Execute.
		*/
		void OpticalFlowExecute() override;

	public:

		/**
		* @brief Get Unit Handle.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::OpticalFlowSession::Handle& Handle() const { return m_Session.GetHandle(); }

	private:

		/**
		* @brief Bind Session Images.
		*/
		void BindSessionImages() const;

	private:

		Unit::OpticalFlowSession m_Session;                // @brief This OpticalFlowSession.
		std::unordered_map<VkOpticalFlowSessionBindingPointNV, class Image*> m_SessionImages;  // @brief Container of Stage Image.
	};
}

#endif