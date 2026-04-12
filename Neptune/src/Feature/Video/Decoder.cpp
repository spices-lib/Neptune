/**
* @file Decoder.cpp.
* @brief The Decoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Decoder.h"
#include "Render/Frontend/RHI/Decoder.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::Video {

	Decoder::Decoder(VideoOperation op)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl = CreateSP<RHI::Decoder>(&op);
	}

	void Decoder::PushNextFrameToRenderTarget()
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->PushNextFrameToRenderTarget();
	}

	void Decoder::ParserDataChunk(uint8_t* data, uint64_t size)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->ParserDataChunk(data, size);
	}

	uint32_t Decoder::GetDecodedTextureCount()
	{
		NEPTUNE_PROFILE_ZONE

		return m_Impl->GetDecodedPictureCount();
	}

	void Decoder::SetDecodeRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetDecodeRenderTarget(renderTarget->GetRHIResource());
	}

	void Decoder::SetReferenceRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetReferenceRenderTarget(renderTarget->GetRHIResource());
	}

	void Decoder::SetFlowVectorRenderTarget(const SP<RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetFlowVectorRenderTarget(renderTarget->GetRHIResource());
	}
}