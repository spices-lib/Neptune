/**
* @file CmdList2.h.
* @brief The CmdList2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Render/Frontend/RHI/CmdList2.h"
#include "CmdList.h"

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::CmdList2 Class.
	* This class defines the Direct3D12::CmdList2 behaves.
	*/
	class CmdList2 : public CmdList, public RHI::RHICmdList2::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		*/
		explicit CmdList2(Context& context) : CmdList(context) {}

		/**
		* @brief Destructor Function.
		*/
		~CmdList2() override = default;

	public:

		/**
		* @brief Interface of Begin CommandList.
		*/
		void Begin() const override;

		/**
		* @brief Interface of End CommandList.
		*/
		void End() const override;

		/**
		* @brief Interface of Submit CommandList and Wait.
		*/
		void SubmitWait() override;

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*/
		void SetGraphicCmdList() override;

		/**
		* @brief Interface of Set VideoDecode CommandList Context.
		*/
		void SetVideoDecodeCmdList() override;

		/**
		* @brief Interface of Set OpticalFlow CommandList Context.
		*/
		void SetOpticalFlowCmdList() override;

	};
}

#endif