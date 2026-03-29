/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Semaphore Class.
	* This class defines the Vulkan::Unit::Semaphore behaves.
	*/
	class Semaphore : public Unit<VkSemaphore, VkObjectType::VK_OBJECT_TYPE_SEMAPHORE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Semaphore() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Semaphore() override;

		/**
		* @brief Create Semaphore.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkSemaphoreCreateInfo.
		*/
		void CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;           // @brief VkDevice.
	};
}