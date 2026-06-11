/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "CmdList.h"
#include "Data/Clock.h"

namespace Neptune::Direct3D11 {

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_FrameIndex = clock.m_FrameIndex;
		m_ImageIndex = clock.m_ImageIndex;
	}

	void* CmdList::GetCommandList() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return nullptr;
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdBindPipeline(const SP<RHI::Pipeline>& pipeline)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdDrawFullScreenTriangle() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdSetViewport(const glm::vec2& viewPortSize) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
	{
		NEPTUNE_PROFILE_ZONE
	}



}

#endif