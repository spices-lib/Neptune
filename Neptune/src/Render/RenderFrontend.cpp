#include "Pchheader.h"
#include "RenderFrontend.h"

namespace Neptune {

	RenderFrontend::RenderFrontend()
	{
		m_RenderBackend = std::make_unique<VulkanRenderBackend>();
	}

	void RenderFrontend::BeginFrame(FrameInfo& frameInfo)
	{
		NEPTUNE_PROFILE_ZONE;

		m_RenderBackend->BeginFrame(frameInfo);
	}

	void RenderFrontend::EndFrame(FrameInfo& frameInfo)
	{
		NEPTUNE_PROFILE_ZONE;

		m_RenderBackend->EndFrame(frameInfo);
	}

	void RenderFrontend::RenderFrame(TimeStep& ts, FrameInfo& frameInfo)
	{
		NEPTUNE_PROFILE_ZONE;

		m_RenderBackend->RenderFrame(ts, frameInfo);
	}

	void RenderFrontend::OnEvent(Event& event)
	{
		NEPTUNE_PROFILE_ZONE;

		m_RenderBackend->OnEvent(event);
	}
}