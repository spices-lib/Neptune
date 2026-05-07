/**
* @file CmdList2.h.
* @brief The CmdList2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RHI/CmdList2.h"
#include "CmdList.h"

namespace Neptune::Vulkan {

	namespace Resource {
		
		class VideoSession;
	}
	
	class ThreadQueue;
	class OpticalFlowSession;

	/**
	* @brief Vulkan::CmdList2 Class.
	* This class defines the Vulkan::CmdList2 behaves.
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

	public:

		/**
		* @brief Set VideoSession.
		* 
		* @param[in] videoSession VideoSession.
		*/
		void SetVideoSession(const WP<Resource::VideoSession>& videoSession);

		/**
		* @brief Set OpticalFlowSession.
		*
		* @param[in] opticalFlowSession OpticalFlowSession.
		*/
		void SetOpticalFlowSession(const OpticalFlowSession* opticalFlowSession);

		/**
		* @brief Begin VideoCoding.
		*
		* @param[in] info VkVideoBeginCodingInfoKHR.
		*/
		void CmdBeginVideoCoding(const VkVideoBeginCodingInfoKHR& info) const;

		/**
		* @brief Control VideoCoding.
		*/
		void CmdControlVideoCoding() const;

		/**
		* @brief DecodeVideo.
		*
		* @param[in] info VkVideoDecodeInfoKHR.
		*/
		void CmdDecodeVideo(const VkVideoDecodeInfoKHR& info) const;

		/**
		* @brief End VideoCoding.
		*/
		void CmdEndVideoCoding() const;

		/**
		* @brief OpticalFlow Execute.
		*/
		void CmdOpticalFlowExecute() const;

	private:

		ThreadQueue*                 m_ThreadQueue;               // @brief ThreadQueue
		WP<Resource::VideoSession>   m_VideoSession;              // @brief VideoSession
		const OpticalFlowSession*    m_OpticalFlowSession;        // @brief OpticalFlowSession
	};
}

#endif