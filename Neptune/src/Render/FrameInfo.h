/**
* @file FrameInfo.h.
* @brief The FrameInfo Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/LinkedUnorderedMap.h"
// STL Header.
#include <memory>

namespace Neptune {

	/**
	* @brief Forward Declare.
	*/
	class World;

	enum class RendererType
	{
		Rasterization,
	};
	
	/**
	* @brief FrameInfo Class.
	* This class defines the FrameInfo data.
	*/
	class FrameInfo
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		FrameInfo() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~FrameInfo() = default;

		/**
		* @brief Copy Constructor Function.
		* @note This Class not allowed copy behaves.
		*/
		FrameInfo(const FrameInfo&) = delete;

		/**
		* @brief Copy Assignment Operation.
		* @note This Class not allowed copy behaves.
		*/
		FrameInfo& operator=(const FrameInfo&) = delete;

		/**
		* @brief Get FrameInfo.
		* @return Returns static FrameInfo reference.
		*/
		static FrameInfo& Get();

	public:

		/**
		* @brief FrameIndex, varying during 0 - (MaxFrameInFlight - 1).
		* Used almost anywhere.
		*/
		uint32_t m_FrameIndex = 0;

		/**
		* @brief ImageIndex, varying during 0 - (MaxFrameInFlight - 1).
		* Used in swapchain index and framebuffer index.
		*/
		uint32_t m_ImageIndex = 0;

		/**
		* @breif A container of mouse picked entity id.
		* key means entity id.
		* value entity tag 0
		*/
		scl::linked_unordered_map<int, std::string> m_PickEntityID{};

		/**
		* @brief Identify of selected material.
		* @note The first value is entity index, the second value is mesh pack index.
		* @attention Not support multiple mesh component in one entity.
		*/
		uint32_t m_PickMaterial = 0;

		/**
		* @brief The shared pointer of specific world.
		*/
		std::shared_ptr<World> m_World;

		/**
		* @brief The renderer type of current world.
		*/
		RendererType m_RendererType = RendererType::Rasterization;
	};
}