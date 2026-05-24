/**
* @file OpticalFlow.h.
* @brief The OpticalFlow Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

	class RenderTarget;

	namespace RHI {

		class OpticalFlow;
	}
}

namespace Neptune::Video {

	/**
	* @brief OpticalFlow Class.
	*/
	class OpticalFlow
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		OpticalFlow();

		/**
		* @brief Destructor Function.
		*/
		virtual~OpticalFlow() = default;

		/**
		* @brief Set Input RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetInputRenderTarget(const SP<RenderTarget>& renderTarget) const;

		/**
		* @brief Set Reference RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetReferenceRenderTarget(const SP<RenderTarget>& renderTarget) const;

		/**
		* @brief Set FlowVector RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetFlowVectorRenderTarget(const SP<RenderTarget>& renderTarget) const;

		/**
		* @brief Create OpticalFlow Session.
		* 
		* @return Returns true if succeeded.
		*/
		bool CreateOpticalFlowSession() const;

		/**
		* @brief OpticalFlow Execute.
		*/
		void OpticalFlowExecute() const;

	private:

		SP<RHI::OpticalFlow> m_Impl;  // @brief This RHI OpticalFlow.

	};

}