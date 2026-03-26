#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"
#include "Render/Frontend/RHI/CmdList2.h"
#include "CmdList.h"

namespace Neptune::Vulkan {

	class ThreadQueue;
	class VideoSession;
	class OpticalFlowSession;

	class CmdList2 : public CmdList, public RHI::RHICmdList2::Impl
	{
	public:

		CmdList2(Context& context) : CmdList(context) {}
		~CmdList2() override = default;

		void Begin() override;

		void End() override;

		void SubmitWait() override;

		void SetGraphicCmdList() override;

		void SetVideoDecodeCmdList() override;

		void SetOpticalFlowCmdList() override;

		void SetVideoSession(SP<VideoSession> videoSession);

		void SetOpticalFlowSession(OpticalFlowSession* opticalFlowSession);

		void CmdBeginVideoCoding(const VkVideoBeginCodingInfoKHR& info) const;

		void CmdControlVideoCoding() const;

		void CmdDecodeVideo(const VkVideoDecodeInfoKHR& info) const;

		void CmdEndVideoCoding() const;

		void CmdOpticalFlowExecute() const;

	private:

		SP<ThreadQueue>        m_ThreadQueue        = nullptr;
		SP<VideoSession>       m_VideoSession       = nullptr;
		OpticalFlowSession* m_OpticalFlowSession = nullptr;
	};
}