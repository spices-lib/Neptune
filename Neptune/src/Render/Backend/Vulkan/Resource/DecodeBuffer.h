/**
* @file DecodeBuffer.h.
* @brief The DecodeBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Buffer.h"
#include <vector>

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::DecodeBuffer Class.
	* This class defines the Vulkan::DecodeBuffer behaves.
	*/
	class DecodeBuffer : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DecodeBuffer(Context& context) : ContextAccessor(context), m_Buffer(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DecodeBuffer() override = default;

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		const VkDeviceSize& Size() const { return m_Buffer.Size(); }

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.Handle(); }

		/**
		* @brief Create Buffer.
		*
		* @param[in] size Buffer Size.
		*/
		void CreateBuffer(VkDeviceSize size = 0);

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		/**
		* @brief Set Slice Start Code.
		*
		* @param[in] index Offset.
		* 
		* @return Returns 3.
		*/
		VkDeviceSize SetSliceStartCodeAtOffset(VkDeviceSize index);

		/**
		* @brief Is Slice Start Code exist.
		*
		* @param[in] indx Offset.
		*
		* @return Returns true if exist.
		*/
		bool HasSliceStartCodeAtOffset(VkDeviceSize indx) const;

		/**
		* @brief Get Buffer Host Data.
		*
		* @return Returns Buffer Host Data.
		*/
		uint8_t* HostData();

		/**
		* @brief Read Buffer Host Data.
		*
		* @param[in] index Offset.
		* 
		* @return Returns Buffer Host Data.
		*/
		uint8_t Read(VkDeviceSize index) const;

		/**
		* @brief Add Stream Marker.
		*
		* @param[in] streamOffset Offset.
		*
		* @return Returns Stream Marker size.
		*/
		uint32_t AddStreamMarker(uint32_t streamOffset);

		/**
		* @brief Reset Stream Marker.
		*
		* @return Returns Stream Marker size.
		*/
		uint32_t ResetStreamMarkers();

		/**
		* @brief Get Stream Marker size.
		*
		* @return Returns Stream Marker size.
		*/
		uint32_t GetStreamMarkersCount() const { return m_StreamMarkers.size(); }

		/**
		* @brief Get Stream Marker data.
		*
		* @param[in] startIndex Offset.
		* @param[out] maxCount .
		* 
		* @return Returns Stream Marker data.
		*/
		const uint32_t* GetStreamMarkersPtr(uint32_t startIndex, uint32_t& maxCount) const;

	private:

		Buffer                   m_Buffer;            // @brief This Buffer
		std::vector<uint32_t>    m_StreamMarkers;     // @brief Stream Marker
	};
}