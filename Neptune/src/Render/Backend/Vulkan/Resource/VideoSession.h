/**
* @file QueryPool.h.
* @brief The QueryPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
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

	/**
	* @brief Vulkan::VideoSession Class.
	* This class defines the Vulkan::VideoSession behaves.
	*/
	class VideoSession : public ContextAccessor
	{
	public:

		using ParameterSets = std::unordered_map<StdVideoPictureParametersSet::ParameterType, std::unordered_map<uint8_t, SP<StdVideoPictureParametersSet>>>;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit VideoSession(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~VideoSession() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::VideoSession::Handle& Handle() const { return m_Session.GetHandle(); }

		/**
		* @brief Get VideoSessionParameters Unit Handle.
		*
		* @return Returns VideoSessionParametersUnit Handle.
		*/
		const Unit::VideoSessionParameters::Handle& Parameters() const { return m_Parameters.GetHandle(); }

		/**
		* @brief Get DecodeBuffer.
		*
		* @return Returns DecodeBuffer.
		*/
		SP<DecodeBuffer> Buffer() { return m_Buffer; }

		/**
		* @brief Create DecodeBuffer.
		*
		* @param[in] size Buffer Size.
		*/
		void CreateBuffer(VkDeviceSize size = 0);

		/**
		* @brief Get DecodePictureBuffer.
		*
		* @return Returns DecodePictureBuffer.
		*/
		DecodePictureBuffer& DPB() { return m_DPB; }

		/**
		* @brief Get DstFormat.
		*
		* @return Returns DstFormat.
		*/
		VkFormat DstFormat() const { return m_DstFormat; }

		/**
		* @brief Get QueryPool.
		*
		* @return Returns QueryPool.
		*/
		SP<QueryPool> GetQueryPool() { return m_QueryPool; }

		/**
		* @brief Create VideoSession.
		*
		* @param[in] profile VkVideoProfileInfoKHR.
		* @param[in] width .
		* @param[in] height .
		* @param[in] slots .
		*/
		void CreateVideoSession(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slots);

		/**
		* @brief Add VideoSessionParameters.
		* 
		* @param[in] param StdVideoPictureParametersSet.
		*/
		void AddVideoSessionParameters(const SP<StdVideoPictureParametersSet>& param);

		/**
		* @brief GetDecode Result.
		*
		* @return Returns true if succeeded.
		*/
		bool GetDecodeResult() const;

		/**
		* @brief Push Display Slot.
		*
		* @param[in] slot Display Slot.
		*/
		void PushDisplaySlot(uint8_t slot);

		/**
		* @brief Pop a Display Slot.
		*
		* @return Returns a Display Slot.
		*/
		uint8_t PopDisplaySlot();
		
		/**
		* @brief Get Display Slot count.
		*
		* @return Returns Display Slot count.
		*/
		uint8_t GetDisplaySlotCount() const { return m_DisplaySlots.size(); }

		/**
		* @brief Create Decode RenderTarget.
		*
		* @param[out] rt Target RenderTarget.
		* @param[in] profile VkVideoProfileInfoKHR.
		* @param[in] width .
		* @param[in] height .
		*/
		void CreateDecodeRenderTarget(class RenderTarget* rt, const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height) const;

		/**
		* @brief Create FlowVector RenderTarget.
		*
		* @param[out] rt Target RenderTarget.
		* @param[in] width .
		* @param[in] height .
		*/
		void CreateFlowVectorRenderTarget(class RenderTarget* rt, uint32_t width, uint32_t height) const;

	private:

		/**
		* @brief Create QueryPool.
		*
		* @param[in] profile VkVideoProfileInfoKHR.
		* @param[in] slot DPB slot count.
		*/
		void CreateQueryPool(const VkVideoProfileInfoKHR& profile, uint32_t slot);

		/**
		* @brief Create VideoSessionParameters.
		*
		* @param[in] op VkVideoCodecOperationFlagsKHR.
		*/
		void CreateVideoSessionParameters(VkVideoCodecOperationFlagsKHR op);

		/**
		* @brief Update VideoSessionParameters.
		*/
		void UpdateVideoSessionParameters();

		/**
		* @brief Create DecodePictureBuffer.
		* 
		* @param[in] profile VkVideoProfileInfoKHR.
		* @param[in] width .
		* @param[in] height .
		* @param[in] slot DPB slot count.
		* @param[in] format VkFormat.
		*/
		void CreateDecodePictureBuffer(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slot, VkFormat format);

		/**
		* @brief Create YcbcrConversion.
		*/
		void CreateSamplerYcbcrConversion();

	private:

		Unit::VideoSession                   m_Session;              // @brief This VideoSession.
		Unit::VideoSessionParameters         m_Parameters;           // @brief This VideoSessionParameters.
		Unit::SamplerYcbcrConversion         m_Conversion;           // @brief This SamplerYcbcrConversion.
		DecodePictureBuffer                  m_DPB;                  // @brief DecodePictureBuffer.
		std::queue<uint8_t>                  m_DisplaySlots;         // @brief Display Slots.
		SP<DecodeBuffer>                     m_Buffer;               // @brief DecodeBuffer.
		SP<QueryPool>                        m_QueryPool;            // @brief QueryPool.
		ParameterSets                        m_ParameterSets;        // @brief ParameterSets.
		VkFormat                             m_DstFormat;            // @brief DstFormat.
	};
}

#endif