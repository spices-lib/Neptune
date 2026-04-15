/**
* @file DescriptorPool.h.
* @brief The DescriptorPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/DescriptorPool.h"

namespace Neptune::Vulkan {

	using IDescriptorPool = InfrastructureClass<class DescriptorPool, EInfrastructure::DescriptorPool>;

	/**
	* @brief Vulkan::DescriptorPool Class.
	* This class defines the Vulkan::DescriptorPool behaves.
	*/
	class DescriptorPool : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		DescriptorPool(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~DescriptorPool() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::DescriptorPool::Handle& Handle() const { return m_DescriptorPool.GetHandle(); }

	private:

		/**
		* @brief Create DescriptorPool.
		*/
		void Create();

	private:

		Unit::DescriptorPool m_DescriptorPool; // @brief this DescriptorPool

	};

}

#endif