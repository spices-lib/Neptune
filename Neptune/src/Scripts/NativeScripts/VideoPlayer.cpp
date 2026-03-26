#include "VideoPlayer.h"
#include "Video/Demuxer.h"
#include "Video/Decoder.h"
#include "Video/OpticalFlow.h"
#include "Resource/ResourcePool.h"
#include "Resource/Texture/RenderTarget.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace Neptune {

	void VideoPlayer::OnAttached()
	{
        m_Demuxer = Demuxer::Create();
		m_Demuxer->Initialize(m_InFile, VideoOperation::DecodeH265);

		m_Decoder = CreateSP<Decoder>(VideoOperation::DecodeH265);

		m_OpticalFlow = CreateSP<OpticalFlow>();

		m_Decoder->SetDecodeRenderTarget(ResourcePool<RenderTarget>::Instance().GetResource("CurrDecodeRT"));

		//m_Decoder->SetReferenceRenderTarget(ResourcePool<RenderTarget>::Instance().CreateResource("PrevDecodeRT"));
		//m_Decoder->SetFlowVectorRenderTarget(ResourcePool<RenderTarget>::Instance().CreateResource("FlowVectorRT"));
	}
	
	void VideoPlayer::OnTick()
	{
		while(!m_Decoder->GetDecodedPictureCount())
		{
			auto packet = m_Demuxer->DemuxFrame();

			m_Decoder->ParserDataChunk(packet);
		}

		/*if (m_FrameCount == 0)
		{
			m_OpticalFlow->SetInputRenderTarget(ResourcePool<RenderTarget>::Instance().GetResource("PrevDecodeRT"));
			m_OpticalFlow->SetReferenceRenderTarget(ResourcePool<RenderTarget>::Instance().GetResource("CurrDecodeRT"));
			m_OpticalFlow->SetFlowVectorRenderTarget(ResourcePool<RenderTarget>::Instance().GetResource("FlowVectorRT"));

			m_OpticalFlow->CreateOpticalFlowSession();
		}*/

		m_Decoder->PushNextFrameToRenderTarget();

		if (m_FrameCount > 0)
		{
			//m_OpticalFlow->OpticalFlowExecute();
		}
		++m_FrameCount;
	}

}