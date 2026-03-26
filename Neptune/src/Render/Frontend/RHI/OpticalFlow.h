#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	class RenderTarget;

	using RHIOpticalFlow = RHI<ERHI::OpticalFlow>;

	template<>
	class RHIOpticalFlow::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetInputRenderTarget(SP<RenderTarget> rt) = 0;

		virtual void SetReferenceRenderTarget(SP<RenderTarget> rt) = 0;

		virtual void SetFlowVectorRenderTarget(SP<RenderTarget> rt) = 0;

		virtual bool CreateOpticalFlowSession() = 0;

		virtual void OpticalFlowExecute() = 0;
	};

	class OpticalFlow : public RHIOpticalFlow
	{
	public:

		OpticalFlow() = default;
		~OpticalFlow() override = default;

		void SetInputRenderTarget(SP<RenderTarget> rt) { RHIOpticalFlow::m_Impl->SetInputRenderTarget(rt); }

		void SetReferenceRenderTarget(SP<RenderTarget> rt) { RHIOpticalFlow::m_Impl->SetReferenceRenderTarget(rt); }

		void SetFlowVectorRenderTarget(SP<RenderTarget> rt) { RHIOpticalFlow::m_Impl->SetFlowVectorRenderTarget(rt); }

		bool CreateOpticalFlowSession() { return RHIOpticalFlow::m_Impl->CreateOpticalFlowSession(); }

		void OpticalFlowExecute() { RHIOpticalFlow::m_Impl->OpticalFlowExecute(); }
	};
}