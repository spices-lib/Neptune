#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/VideoSession.h"
#include "Render/Backend/Vulkan/Unit/VideoSessionParameters.h"
#include "Render/Backend/Vulkan/VideoParser/STD/StdVideoPictureParametersSet.h"
#include "Render/Backend/Vulkan/Resource/DecodePictureBuffer.h"
#include "Render/Backend/Vulkan/Unit/SamplerYcbcrConversion.h"
#include <unordered_map>
#include <queue>

namespace Neptune::Vulkan {

	class DecodeBuffer;
	class QueryPool;

	class VideoSession : public ContextAccessor
	{
	public:

		using ParameterSets = std::unordered_map<StdVideoPictureParametersSet::ParameterType, std::unordered_map<uint8_t, SP<StdVideoPictureParametersSet>>>;

	public:

		VideoSession(Context& context);
		~VideoSession() override = default;

		const Unit::VideoSession::Handle& Handle() const { return m_Session.GetHandle(); }

		const Unit::VideoSessionParameters::Handle& Parameters() const { return m_Parameters.GetHandle(); }

		SP<DecodeBuffer> Buffer() { return m_Buffer; }

		void CreateBuffer(VkDeviceSize size = 0);

		DecodePictureBuffer& DPB() { return m_DPB; }

		VkFormat DstFormat() const { return m_DstFormat; }

		SP<QueryPool> GetQueryPool() { return m_QueryPool; }

		void CreateVideoSession(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slots);

		void AddVideoSessionParameters(SP<StdVideoPictureParametersSet> param);

		bool GetDecodeResult();

		void PushDisplaySlot(uint8_t slot);

		uint8_t PopDisplaySlot();
		
		uint8_t GetDisplaySlotCount() const { return m_DisplaySlots.size(); }

		void CreateDecodeRenderTarget(SP<class RenderTarget> rt, const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height);

		void CreateFlowVectorRenderTarget(SP<class RenderTarget> rt, uint32_t width, uint32_t height);

	private:

		void CreateQueryPool(const VkVideoProfileInfoKHR& profile, uint32_t slot);

		void CreateVideoSessionParameters(VkVideoCodecOperationFlagsKHR op);

		void UpdateVideoSessionParameters();

		void CreateDecodePictureBuffer(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slot, VkFormat format);

		void CreateSamplerYcbcrConversion();

	private:

		Unit::VideoSession                   m_Session;
		Unit::VideoSessionParameters         m_Parameters;
		Unit::SamplerYcbcrConversion         m_Conversion;
		DecodePictureBuffer                  m_DPB;
		std::queue<uint8_t>                  m_DisplaySlots;
		SP<DecodeBuffer>                     m_Buffer;
		SP<QueryPool>                        m_QueryPool;
		ParameterSets                        m_ParameterSets;
		VkFormat                             m_DstFormat;
	};
}