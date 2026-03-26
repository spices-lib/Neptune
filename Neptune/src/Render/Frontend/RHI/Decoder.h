#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	class RenderTarget;

	using RHIDecoder = RHI<ERHI::Decoder>;

	template<>
	class RHIDecoder::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void ParserDataChunk(uint8_t* data, uint64_t size) = 0;

		virtual uint32_t GetDecodedPictureCount() = 0;

		virtual void SetDecodeRenderTarget(SP<RenderTarget> renderTarget) = 0;

		virtual void SetReferenceRenderTarget(SP<RenderTarget> renderTarget) = 0;

		virtual void SetFlowVectorRenderTarget(SP<RenderTarget> renderTarget) = 0;

		virtual void PushNextFrameToRenderTarget() = 0;
	};

	class Decoder : public RHIDecoder
	{
	public:

		Decoder(void* payload) : RHIDecoder(payload) {}
		~Decoder() override = default;

		void ParserDataChunk(uint8_t* data, uint64_t size) { RHIDecoder::m_Impl->ParserDataChunk(data, size); }

		uint32_t GetDecodedPictureCount() { return RHIDecoder::m_Impl->GetDecodedPictureCount(); }

		void SetDecodeRenderTarget(SP<RenderTarget> renderTarget) { return RHIDecoder::m_Impl->SetDecodeRenderTarget(renderTarget); }

		void SetReferenceRenderTarget(SP<RenderTarget> renderTarget) { return RHIDecoder::m_Impl->SetReferenceRenderTarget(renderTarget); }

		void SetFlowVectorRenderTarget(SP<RenderTarget> renderTarget) { return RHIDecoder::m_Impl->SetFlowVectorRenderTarget(renderTarget); }

		void PushNextFrameToRenderTarget() { return RHIDecoder::m_Impl->PushNextFrameToRenderTarget(); }
	};
}