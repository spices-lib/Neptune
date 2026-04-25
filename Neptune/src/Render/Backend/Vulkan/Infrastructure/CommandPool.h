/**
* @file CommandPool.h.
* @brief The CommandPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandPool.h"

namespace Neptune::Vulkan {

	using IGraphicCommandPool     = IInfrastructure<class CommandPool, EInfrastructure::GraphicCommandPool>;
	using IComputeCommandPool     = IInfrastructure<class CommandPool, EInfrastructure::ComputeCommandPool>;

	/**
	* @brief Vulkan::CommandPool Class.
	* This class defines the Vulkan::CommandPool behaves.
	*/
	class CommandPool : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		CommandPool(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~CommandPool() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::CommandPool::Handle& Handle() const { return m_CommandPool.GetHandle(); }

	private:

		/**
		* @brief Create CommandPool.
		*/
		void Create();

		/**
		* @brief Get CommandPool QueueFamily.
		* 
		* @return Returns CommandPool QueueFamily.
		*/
		uint32_t GetQueueFamily() const;

	private:

		Unit::CommandPool m_CommandPool; // @brief this CommandPool.

	};

}

#endif