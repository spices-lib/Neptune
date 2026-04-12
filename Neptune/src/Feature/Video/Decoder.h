/**
* @file Decoder.h.
* @brief The Decoder Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Demuxer.h"

namespace Neptune {

	class RenderTarget;

	namespace RHI {

		class Decoder;
	}
}

namespace Neptune::Video {

	/**
	* @brief Video Decoder Class.
	*/
	class Decoder
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] op VideoOperation.
		*/
		Decoder(VideoOperation op);

		/**
		* @brief Destructor Function.
		*/
		virtual~Decoder() = default;

		/**
		* @brief Push next frame to RT.
		*/
		void PushNextFrameToRenderTarget();

		/**
		* @brief Parse DataChunk.
		* 
		* @param[in] data Video data.
		* @param[in] size Video data size.
		*/
		void ParserDataChunk(uint8_t* data, uint64_t size);

		/**
		* @brief Get Decoded Texture Count.
		*
		* @param[in] data Video data.
		* @param[in] size Video data size.
		*/
		uint32_t GetDecodedTextureCount();

		/**
		* @brief Set Decode RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetDecodeRenderTarget(const SP<RenderTarget>& renderTarget);

		/**
		* @brief Set Reference RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetReferenceRenderTarget(const SP<RenderTarget>& renderTarget);

		/**
		* @brief Set FlowVector RenderTarget.
		*
		* @param[in] renderTarget RenderTarget.
		*/
		void SetFlowVectorRenderTarget(const SP<RenderTarget>& renderTarget);

	private:

		SP<RHI::Decoder> m_Impl;   // @brief This RHI Decoder.

	};

}