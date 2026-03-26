#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include <glm/glm.hpp>

namespace Neptune::Data {

	struct Clock;

}

namespace Neptune::RHI {

	using RHICmdList = RHI<ERHI::CmdList>;

	template<>
	class RHICmdList::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetGraphicCmdList(const Data::Clock& clock) = 0;

		virtual void SetRenderPass(SP<class RenderPass> renderPass) = 0;

		virtual void CmdDrawSlate() const = 0;

		virtual void CmdBeginRenderPass() const = 0;

		virtual void CmdEndRenderPass() const = 0;

		virtual void CmdBindDescriptor(SP<class DescriptorList> descriptorList) const = 0;

		virtual void CmdBindPipeline(SP<class Pipeline> pipeline) = 0;

		virtual void CmdDrawFullScreenTriangle() const = 0;

		virtual void CmdSetViewport(const glm::vec2& viewPortSize) const = 0;
	};

	class CmdList : public RHICmdList
	{
	public:

		CmdList() = default;
		~CmdList() override = default;

		void SetGraphicCmdList(const Data::Clock& clock) { RHICmdList::m_Impl->SetGraphicCmdList(clock); }

		void SetRenderPass(SP<class RenderPass> renderPass) { RHICmdList::m_Impl->SetRenderPass(renderPass); }

		void CmdDrawSlate() const { RHICmdList::m_Impl->CmdDrawSlate(); }

		void CmdBeginRenderPass() const { RHICmdList::m_Impl->CmdBeginRenderPass(); }

		void CmdEndRenderPass() const { RHICmdList::m_Impl->CmdEndRenderPass(); }

		void CmdBindDescriptor(SP<class DescriptorList> descriptorList) const { RHICmdList::m_Impl->CmdBindDescriptor(descriptorList); }

		void CmdBindPipeline(SP<class Pipeline> pipeline) { RHICmdList::m_Impl->CmdBindPipeline(pipeline); }

		void CmdDrawFullScreenTriangle() const { RHICmdList::m_Impl->CmdDrawFullScreenTriangle(); }

		void CmdSetViewport(const glm::vec2& viewPortSize) const { RHICmdList::m_Impl->CmdSetViewport(viewPortSize); }
	};
}