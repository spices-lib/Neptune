/**
* @file Decoder.h.
* @brief The Decoder Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	class RenderTarget;

	using RHIDecoder = RHI<ERHI::Decoder>;

	/**
	* @brief Specialization of RHIDecoder::Impl
	*/
	template<>
	class RHIDecoder::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;

		/**
		* @brief Interface of Parser DataChunk.
		* 
		* @param[in] data .
		* @param[in] size .
		*/
		virtual void ParserDataChunk(uint8_t* data, uint64_t size) = 0;

		/**
		* @brief Interface of Get Decoded Picture Count.
		*
		* @return Returns Decoded Picture Count.
		*/
		virtual uint32_t GetDecodedPictureCount() = 0;

		/**
		* @brief Interface of Set Decode RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		virtual void SetDecodeRenderTarget(SP<RenderTarget> renderTarget) = 0;

		/**
		* @brief Interface of Set Reference RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		virtual void SetReferenceRenderTarget(SP<RenderTarget> renderTarget) = 0;

		/**
		* @brief Interface of Set FlowVector RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		virtual void SetFlowVectorRenderTarget(SP<RenderTarget> renderTarget) = 0;

		/**
		* @brief Interface of Push NextFrame to RenderTarget.
		*/
		virtual void PushNextFrameToRenderTarget() = 0;
	};

	/**
	* @brief RHI of ERHI::Decoder
	*/
	class Decoder : public RHIDecoder
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Decoder(void* payload) : RHIDecoder(payload) {}

		/**
		* @brief Destructor Function.
		*/
		~Decoder() override = default;

		/**
		* @brief Interface of Parser DataChunk.
		*
		* @param[in] data .
		* @param[in] size .
		*/
		void ParserDataChunk(uint8_t* data, uint64_t size) const { RHIDecoder::m_Impl->ParserDataChunk(data, size); }

		/**
		* @brief Interface of Get Decoded Picture Count.
		*
		* @return Returns Decoded Picture Count.
		*/
		uint32_t GetDecodedPictureCount() const { return RHIDecoder::m_Impl->GetDecodedPictureCount(); }

		/**
		* @brief Interface of Set Decode RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetDecodeRenderTarget(SP<RenderTarget> renderTarget) const { return RHIDecoder::m_Impl->SetDecodeRenderTarget(renderTarget); }

		/**
		* @brief Interface of Set Reference RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetReferenceRenderTarget(SP<RenderTarget> renderTarget) const { return RHIDecoder::m_Impl->SetReferenceRenderTarget(renderTarget); }

		/**
		* @brief Interface of Set FlowVector RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetFlowVectorRenderTarget(SP<RenderTarget> renderTarget) const { return RHIDecoder::m_Impl->SetFlowVectorRenderTarget(renderTarget); }

		/**
		* @brief Interface of Push NextFrame to RenderTarget.
		*/
		void PushNextFrameToRenderTarget() const { return RHIDecoder::m_Impl->PushNextFrameToRenderTarget(); }
	};
}