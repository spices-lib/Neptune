/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Shader.h"
#include "Render/Frontend/RHI/Shader.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::Shader Class.
	* This class defines the Vulkan::Shader behaves.
	*/
	class Shader : public ContextAccessor, public RHI::RHIShader::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Shader(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Shader() override = default;

	public:

		/**
		* @brief Interface of Set Shader Source.
		*
		* @param[in] source Shader Source.
		*/
		void SetSource(const std::vector<uint8_t>& source) override;

		/**
		* @brief Interface of Set Shader Name.
		*
		* @param[in] name Shader Name.
		*/
		void SetName(const std::string& name) override;

	public:

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Shader::Handle& Handle() const { return m_Shader.GetHandle(); }

	private:

		Unit::Shader m_Shader;          // @brief This Shader.
	};
}

#endif