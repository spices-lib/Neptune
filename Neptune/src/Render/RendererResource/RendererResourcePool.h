/**
* @file RendererResourcePool.h.
* @brief The RendererResourcePool Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RendererResource.h"

#include <unordered_map>
#include <memory>

namespace Neptune {

	class VulkanImage;
	/**
	* @brief RendererResourcePool Class.
	* This class is a pool of all framebuffer's attachment.
	*/
	class RendererResourcePool
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		RendererResourcePool() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~RendererResourcePool() = default;

		/**
		* @brief Copy Constructor Function.
		* @note This Class not allowed copy behave.
		*/
		RendererResourcePool(const RendererResourcePool&) = delete;

		/**
		* @brief Copy Assignment Operation.
		* @note This Class not allowed copy behave.
		*/
		RendererResourcePool& operator=(const RendererResourcePool&) = delete;

		/**
		* @brief Event Called on Slate resize.
		* @param[in] width Slate new width.
		* @param[in] height Slate new height.
		*/
		void OnSlateResize(uint32_t width, uint32_t height) const;


	private:

		/**
		* @brief The hashmap of all RendererResource.
		*/
		std::unordered_map<std::string, std::unique_ptr<RendererResource>> m_RendererResource;
	};
}