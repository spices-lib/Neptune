/**
* @file CmdList.h.
* @brief The CmdList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

#include <glm/glm.hpp>

namespace Neptune::Data {

	struct Clock;
}

namespace Neptune::RHI {

	using RHICmdList = RHI<ERHI::CmdList>;

	/**
	* @brief Specialization of RHICmdList::Impl
	*/
	template<>
	class RHICmdList::Impl
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

		/***********************************************************************************/

		/********************************** Context ****************************************/

		/**
		* @brief Interface of Set Graphic CommandList Context.
		* 
		* @param[in] clock Clock.
		*/
		virtual void SetGraphicCmdList(const Data::Clock& clock) = 0;

		/***********************************************************************************/

		/********************************* Reference ***************************************/

		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		virtual void SetRenderPass(const SP<class RenderPass>& renderPass) = 0;

		/***********************************************************************************/

		/********************************* Commands ****************************************/

		/**
		* @brief Interface of DrawSlate.
		*/
		virtual void CmdDrawSlate() const = 0;

		/**
		* @brief Interface of BeginRenderPass.
		*/
		virtual void CmdBeginRenderPass() const = 0;

		/**
		* @brief Interface of EndRenderPass.
		*/
		virtual void CmdEndRenderPass() const = 0;

		/**
		* @brief Interface of BindDescriptor.
		* 
		* @param[in] descriptorList DescriptorList.
		*/
		virtual void CmdBindDescriptor(const SP<class DescriptorList>& descriptorList) const = 0;

		/**
		* @brief Interface of BindPipeline.
		* 
		* @param[in] pipeline Pipeline.
		*/
		virtual void CmdBindPipeline(const SP<class Pipeline>& pipeline) = 0;

		/**
		* @brief Interface of DrawFullScreenTriangle.
		*/
		virtual void CmdDrawFullScreenTriangle() const = 0;

		/**
		* @brief Interface of SetViewport.
		* 
		* @param[in] viewPortSize .
		*/
		virtual void CmdSetViewport(const glm::vec2& viewPortSize) const = 0;

		/***********************************************************************************/
	};

	/**
	* @brief RHI of ERHI::CmdList
	*/
	class CmdList : public RHICmdList
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		CmdList() = default;

		/**
		* @brief Destructor Function.
		*/
		~CmdList() override = default;

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetGraphicCmdList(const Data::Clock& clock) const { RHICmdList::m_Impl->SetGraphicCmdList(clock); }

		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<class RenderPass>& renderPass) const { RHICmdList::m_Impl->SetRenderPass(renderPass); }

		/**
		* @brief Interface of DrawSlate.
		*/
		void CmdDrawSlate() const { RHICmdList::m_Impl->CmdDrawSlate(); }

		/**
		* @brief Interface of BeginRenderPass.
		*/
		void CmdBeginRenderPass() const { RHICmdList::m_Impl->CmdBeginRenderPass(); }

		/**
		* @brief Interface of EndRenderPass.
		*/
		void CmdEndRenderPass() const { RHICmdList::m_Impl->CmdEndRenderPass(); }

		/**
		* @brief Interface of BindDescriptor.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void CmdBindDescriptor(const SP<class DescriptorList>& descriptorList) const { RHICmdList::m_Impl->CmdBindDescriptor(descriptorList); }

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<class Pipeline>& pipeline) const { RHICmdList::m_Impl->CmdBindPipeline(pipeline); }

		/**
		* @brief Interface of DrawFullScreenTriangle.
		*/
		void CmdDrawFullScreenTriangle() const { RHICmdList::m_Impl->CmdDrawFullScreenTriangle(); }

		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::vec2& viewPortSize) const { RHICmdList::m_Impl->CmdSetViewport(viewPortSize); }
	};
}