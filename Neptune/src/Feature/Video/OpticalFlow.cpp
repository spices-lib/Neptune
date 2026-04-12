/**
* @file OpticalFlow.cpp.
* @brief The OpticalFlow Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "OpticalFlow.h"
#include "Render/Frontend/RHI/OpticalFlow.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::Video {

	OpticalFlow::OpticalFlow()
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl = CreateSP<RHI::OpticalFlow>();
	}

	void OpticalFlow::SetInputRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetInputRenderTarget(renderTarget->GetRHIResource());
	}

	void OpticalFlow::SetReferenceRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetReferenceRenderTarget(renderTarget->GetRHIResource());
	}

	void OpticalFlow::SetFlowVectorRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetFlowVectorRenderTarget(renderTarget->GetRHIResource());
	}

	bool OpticalFlow::CreateOpticalFlowSession()
	{
		NEPTUNE_PROFILE_ZONE

		return m_Impl->CreateOpticalFlowSession();
	}

	void OpticalFlow::OpticalFlowExecute()
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->OpticalFlowExecute();
	}
}