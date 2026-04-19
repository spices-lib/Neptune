/**
* @file CmdList2.cpp.
* @brief The CmdList2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "CmdList2.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadCommandPool.h"
#include "Render/Backend/Vulkan/Infrastructure/Functions.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/Queue.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadQueue.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Resource/VideoSession.h"
#include "Render/Backend/Vulkan/RHI/OpticalFlowSession.h"

namespace Neptune::Vulkan {

	void CmdList2::Begin() const
	{
		NEPTUNE_PROFILE_ZONE

		VkCommandBufferBeginInfo               beginInfo{};
		beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo           = nullptr;

		m_CommandBuffer->Begin(beginInfo);
	}

	void CmdList2::End() const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->End();
	}

	void CmdList2::SubmitWait()
	{
		NEPTUNE_PROFILE_ZONE

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
		NEPTUNE_PROFILE_ZONE

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
		NEPTUNE_PROFILE_ZONE

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
		NEPTUNE_PROFILE_ZONE

		VkCommandBufferAllocateInfo            allocInfo{};
		allocInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool                = GetContext().Get<IOpticalFlowThreadCommandPool>()->Handle();
		allocInfo.level                      = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount         = 1;

		m_CommandBuffer = CreateSP<Unit::CommandBuffer>();

		m_CommandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

		m_ThreadQueue = GetContext().Get<IOpticalFlowThreadQueue>();
	}

	void CmdList2::SetVideoSession(const WP<VideoSession>& videoSession)
	{
		NEPTUNE_PROFILE_ZONE

		m_VideoSession = videoSession;
	}

	void CmdList2::SetOpticalFlowSession(const OpticalFlowSession* opticalFlowSession)
	{
		NEPTUNE_PROFILE_ZONE

		m_OpticalFlowSession = opticalFlowSession;
	}

	void CmdList2::CmdBeginVideoCoding(const VkVideoBeginCodingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->BeginVideoCoding(GetContext().Get<IFunctions>()->vkCmdBeginVideoCodingKHR, info);
	}

	void CmdList2::CmdControlVideoCoding() const
	{
		NEPTUNE_PROFILE_ZONE

		VkVideoCodingControlInfoKHR                  controlInfo{};
		controlInfo.sType                          = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
		controlInfo.flags                          = VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR;
		controlInfo.pNext                          = nullptr;

		m_CommandBuffer->ControlVideoCoding(GetContext().Get<IFunctions>()->vkCmdControlVideoCodingKHR, controlInfo);
	}

	void CmdList2::CmdDecodeVideo(const VkVideoDecodeInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->DecodeVideo(GetContext().Get<IFunctions>()->vkCmdDecodeVideoKHR, info);
	}

	void CmdList2::CmdEndVideoCoding() const
	{
		NEPTUNE_PROFILE_ZONE

		VkVideoEndCodingInfoKHR                      info{};
		info.sType                                 = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;

		m_CommandBuffer->EndVideoCoding(GetContext().Get<IFunctions>()->vkCmdEndVideoCodingKHR, info);
	}

	void CmdList2::CmdOpticalFlowExecute() const
	{
		NEPTUNE_PROFILE_ZONE

		VkOpticalFlowExecuteInfoNV                   info{};
		info.sType                                 = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
		info.flags                                 = 0;

		m_CommandBuffer->OpticalFlowExecute(GetContext().Get<IFunctions>()->vkCmdOpticalFlowExecuteNV, m_OpticalFlowSession->Handle(), info);
	}
}

#endif