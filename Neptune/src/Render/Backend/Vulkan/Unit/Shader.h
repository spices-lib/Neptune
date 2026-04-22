/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Shader Class.
	* This class defines the Vulkan::Unit::Shader behaves.
	*/
	class Shader : public Common::Unit<VkShaderModule, VkObjectType::VK_OBJECT_TYPE_SHADER_MODULE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Shader() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Shader() override;

		/**
		* @brief Create Semaphore.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkShaderModuleCreateInfo.
		*/
		void CreateShader(VkDevice device, const VkShaderModuleCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;         // @brief VkDevice.
	};
}

#endif