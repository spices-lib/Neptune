#include "Pchheader.h"
#include "CmdList2.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadCommandPool.h"
#include "Render/Backend/Vulkan/Infrastructure/Functions.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/Queue.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadQueue.h"
#include "Render/Backend/Vulkan/Resource/VideoSession.h"
#include "Render/Backend/Vulkan/RHI/OpticalFlowSession.h"
#include "World/Component/ClockComponent.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan {

	void CmdList2::Begin()
	{
		VkCommandBufferBeginInfo               beginInfo{};
		beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo           = nullptr;

		m_CommandBuffer->Begin(beginInfo);
	}

	void CmdList2::End()
	{
		m_CommandBuffer->End();
	}

	void CmdList2::SubmitWait()
	{
		VkSubmitInfo                           submitInfo{};
		submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount        = 1;
		submitInfo.pCommandBuffers           = &m_CommandBuffer->GetHandle();

		auto queue = m_ThreadQueue->Pop();

		DEBUGUTILS_BEGINQUEUELABEL(queue->GetHandle(), m_ThreadQueue->ToString())

		queue->Submit(submitInfo);

		queue->Wait();

		DEBUGUTILS_ENDQUEUELABEL(queue->GetHandle())

		m_ThreadQueue->Push(queue);

		m_CommandBuffer.reset();
	}

	void CmdList2::SetGraphicCmdList()
	{
		VkCommandBufferAllocateInfo            allocInfo{};
		allocInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool                = GetContext().Get<IGraphicThreadCommandPool>()->Handle();
		allocInfo.level                      = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount         = 1;

		m_CommandBuffer = CreateSP<Unit::CommandBuffer>();

		m_CommandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

		m_ThreadQueue = GetContext().Get<IGraphicThreadQueue>();

		m_BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	}

	void CmdList2::SetVideoDecodeCmdList()
	{
		VkCommandBufferAllocateInfo            allocInfo{};
		allocInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool                = GetContext().Get<IVideoDecodeThreadCommandPool>()->Handle();
		allocInfo.level                      = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount         = 1;

		m_CommandBuffer = CreateSP<Unit::CommandBuffer>();

		m_CommandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

		m_ThreadQueue = GetContext().Get<IVideoDecodeThreadQueue>();
	}

	void CmdList2::SetOpticalFlowCmdList()
	{
		VkCommandBufferAllocateInfo            allocInfo{};
		allocInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool                = GetContext().Get<IOpticalFlowThreadCommandPool>()->Handle();
		allocInfo.level                      = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount         = 1;

		m_CommandBuffer = CreateSP<Unit::CommandBuffer>();

		m_CommandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

		m_ThreadQueue = GetContext().Get<IOpticalFlowThreadQueue>();
	}

	void CmdList2::SetVideoSession(SP<VideoSession> videoSession)
	{
		m_VideoSession = videoSession;
	}

	void CmdList2::SetOpticalFlowSession(OpticalFlowSession* opticalFlowSession)
	{
		m_OpticalFlowSession = opticalFlowSession;
	}

	void CmdList2::CmdBeginVideoCoding(const VkVideoBeginCodingInfoKHR& info) const
	{
		m_CommandBuffer->BeginVideoCoding(GetContext().Get<IFunctions>()->vkCmdBeginVideoCodingKHR, info);
	}

	void CmdList2::CmdControlVideoCoding() const
	{
		VkVideoCodingControlInfoKHR                  controlInfo{};
		controlInfo.sType                          = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
		controlInfo.flags                          = VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR;
		controlInfo.pNext                          = nullptr;

		m_CommandBuffer->ControlVideoCoding(GetContext().Get<IFunctions>()->vkCmdControlVideoCodingKHR, controlInfo);
	}

	void CmdList2::CmdDecodeVideo(const VkVideoDecodeInfoKHR& info) const
	{
		m_CommandBuffer->DecodeVideo(GetContext().Get<IFunctions>()->vkCmdDecodeVideoKHR, info);
	}

	void CmdList2::CmdEndVideoCoding() const
	{
		VkVideoEndCodingInfoKHR                      info{};
		info.sType                                 = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;

		m_CommandBuffer->EndVideoCoding(GetContext().Get<IFunctions>()->vkCmdEndVideoCodingKHR, info);
	}

	void CmdList2::CmdOpticalFlowExecute() const
	{
		VkOpticalFlowExecuteInfoNV                   info{};
		info.sType                                 = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
		info.flags                                 = 0;

		m_CommandBuffer->OpticalFlowExecute(GetContext().Get<IFunctions>()->vkCmdOpticalFlowExecuteNV, m_OpticalFlowSession->Handle(), info);
	}
}