/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Semaphore.h"

#include <vector>

namespace Neptune::Vulkan {

	using IGraphicImageSemaphore     = IInfrastructure<class Semaphore, EInfrastructure::GraphicImageSemaphore>;
	using IGraphicQueueSemaphore     = IInfrastructure<class Semaphore, EInfrastructure::GraphicQueueSemaphore>;
	using IComputeQueueSemaphore     = IInfrastructure<class Semaphore, EInfrastructure::ComputeQueueSemaphore>;

	/**
	* @brief Vulkan::Semaphore Class.
	* This class defines the Vulkan::Semaphore behaves.
	*/
	class Semaphore : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Semaphore Count.
		*/
		Semaphore(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~Semaphore() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] index Semaphore index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::Semaphore::Handle& Handle(uint32_t index = 0) const { return m_Semaphores[index]->GetHandle(); }

	private:

		/**
		* @brief Create Semaphore.
		* 
		* @param[in] count Semaphore count.
		*/
		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Semaphore>> m_Semaphores;    // @brief Container of Semaphore.

	};

}

#endif