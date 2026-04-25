/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/SwapChain.h"

namespace Neptune::Direct3D12::GLFW {

	/**
	* @brief Direct3D12::GLFW::SwapChain Class.
	* This class defines the Direct3D12::GLFW::SwapChain behaves.
	*/
	class SwapChain : public Direct3D12::SwapChain
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count SwapChain image Count.
		* @param[in] window Native window.
		*/
		SwapChain(Context& context, EInfrastructure e, uint32_t count, void* window);

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override = default;

	private:

		/**
		* @brief Create SwapChain.
		*
		* @param[in] count SwapChain image count.
		* @param[in] window Native window.
		*/
		void Create(uint32_t count, void* window);

	};

}

#endif