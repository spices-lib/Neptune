/**
* @file SlatePass.h.
* @brief The SlatePass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Frontend/RenderDelegate.h"
#include "Pass.h"

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class Descriptor;
}

namespace Neptune::Render {

	/**
	* @brief Slate Pass.
	*/
	class SlatePass : public Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		SlatePass() : Pass() {}

		/**
		* @brief Destructor Function.
		*/
		~SlatePass() override = default;

		/**
		* @brief Interface of Construct.
		*/
		void OnConstruct() override;

		/**
		* @brief Interface of Render.
		* 
		* @param[in] scene Scene.
		*/
		void OnRender(Scene* scene) override;

		/**
		* @brief Get RenderPass.
		*
		* @return Returns RenderPass.
		*/
		SP<RHI::RenderPass> GetRenderPass() { return m_RenderPass; }

		/**
		* @brief Set DelegateDrawSlate.
		*
		* @param[in] delegate DelegateDrawSlate.
		*/
		void SetDelegateDrawSlate(const DelegateDrawSlate& delegate) { m_OnDelegateDrawSlate = delegate; }
		
	private:

		SP<RHI::RenderPass> m_RenderPass;          // @brief This RenderPass
		DelegateDrawSlate m_OnDelegateDrawSlate;   // @brief DelegateDrawSlate
	};
}