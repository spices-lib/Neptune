/**
* @file CmdList2.h.
* @brief The CmdList2 Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "CmdList.h"
#include "RHI.h"

namespace Neptune::RHI {

	using RHICmdList2 = RHI<ERHI::CmdList2>;

	/**
	* @brief Specialization of RHICmdList2::Impl
	*/
	template<>
	class RHICmdList2::Impl
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

		/******************************** Life Control *************************************/

		/**
		* @brief Interface of Begin CommandList.
		*/
		virtual void Begin() = 0;

		/**
		* @brief Interface of End CommandList.
		*/
		virtual void End() = 0;

		/**
		* @brief Interface of Submit CommandList and Wait.
		*/
		virtual void SubmitWait() = 0;

		/***********************************************************************************/

		/********************************** Context ****************************************/

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*/
		virtual void SetGraphicCmdList() = 0;

		/**
		* @brief Interface of Set VideoDecode CommandList Context.
		*/
		virtual void SetVideoDecodeCmdList() = 0;

		/**
		* @brief Interface of Set OpticalFlow CommandList Context.
		*/
		virtual void SetOpticalFlowCmdList() = 0;

		/***********************************************************************************/
	};

	/**
	* @brief RHI of ERHI::CmdList2
	*/
	class CmdList2 : public CmdList, public RHICmdList2
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		CmdList2() = default;

		/**
		* @brief Destructor Function.
		*/
		~CmdList2() override = default;

		/**
		* @brief Interface of Begin CommandList.
		*/
		void Begin() const { RHICmdList2::m_Impl->Begin(); }

		/**
		* @brief Interface of End CommandList.
		*/
		void End() const { RHICmdList2::m_Impl->Begin(); }

		/**
		* @brief Interface of Submit CommandList and Wait.
		*/
		void SubmitWait() const { RHICmdList2::m_Impl->SubmitWait(); }

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*/
		void SetGraphicCmdList() const { RHICmdList2::m_Impl->SetGraphicCmdList(); }

		/**
		* @brief Interface of Set VideoDecode CommandList Context.
		*/
		void SetVideoDecodeCmdList() const { RHICmdList2::m_Impl->SetVideoDecodeCmdList(); }

		/**
		* @brief Interface of Set OpticalFlow CommandList Context.
		*/
		void SetOpticalFlowCmdList() const { RHICmdList2::m_Impl->SetOpticalFlowCmdList(); }
	};
}