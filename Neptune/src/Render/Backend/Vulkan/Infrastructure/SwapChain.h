/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/SwapChain.h"
#include "Render/Backend/Vulkan/Resource/Image.h"

namespace Neptune::Vulkan {

	using ISwapChain = IInfrastructure<class SwapChain, EInfrastructure::SwapChain>;

	/**
	* @brief Vulkan::SwapChain Class.
	* This class defines the Vulkan::SwapChain behaves.
	*/
	class SwapChain : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count SwapChain image Count.
		*/
		SwapChain(Context& context, EInfrastructure e, uint32_t count);

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::SwapChain::Handle& Handle() const { return m_SwapChain->GetHandle(); }

		/**
		* @brief Get Next SwapChain Image.
		*
		* @param[in] semaphore VkSemaphore.
		* @param[out] imageIndex Next SwapChain Image index.
		* 
		* @return Returns true if found.
		*/
		bool GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const;

		/**
		* @brief Get ImageView Unit Handle.
		*
		* @param[in] index ImageView index.
		* 
		* @return Returns ImageView Unit Handle.
		*/
		const Unit::ImageView::Handle& GetView(uint32_t index) const { return m_SwapChainImage[index]->GetView(); }

		/**
		* @brief Present to surface.
		*
		* @param[in] info VkPresentInfoKHR.
		*
		* @return Returns true if succeed.
		*/
		bool Present(VkPresentInfoKHR& info) const;

	private:

		/**
		* @brief Create SwapChain.
		*
		* @param[in] count SwapChain image count.
		*/
		void Create(uint32_t count);

	private:

		SP<Unit::SwapChain> m_SwapChain;           // @brief This SwapChain.
		std::vector<SP<Image>> m_SwapChainImage;   // @brief Conatiner of SwapChainImage.

	};

}

#endif