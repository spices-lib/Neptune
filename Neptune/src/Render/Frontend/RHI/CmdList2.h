#pragma once
#include "Core/Core.h"
#include "CmdList.h"
#include "RHI.h"
#include <glm/glm.hpp>

namespace Neptune::RHI {

	using RHICmdList2 = RHI<ERHI::CmdList2>;

	template<>
	class RHICmdList2::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void Begin() = 0;

		virtual void End() = 0;

		virtual void SubmitWait() = 0;

		virtual void SetGraphicCmdList() = 0;

		virtual void SetVideoDecodeCmdList() = 0;

		virtual void SetOpticalFlowCmdList() = 0;
	};

	class CmdList2 : public CmdList, public RHICmdList2
	{
	public:

		CmdList2() = default;
		~CmdList2() override = default;

		void Begin() { RHICmdList2::m_Impl->Begin(); }

		void End() { RHICmdList2::m_Impl->Begin(); }

		void SubmitWait() { RHICmdList2::m_Impl->SubmitWait(); }

		void SetGraphicCmdList() { RHICmdList2::m_Impl->SetGraphicCmdList(); }

		void SetVideoDecodeCmdList() { RHICmdList2::m_Impl->SetVideoDecodeCmdList(); }

		void SetOpticalFlowCmdList() { RHICmdList2::m_Impl->SetOpticalFlowCmdList(); }
	};
}