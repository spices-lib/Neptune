/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Render/Frontend/RHI/Shader.h"

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::Shader Class.
	* This class defines the Direct3D12::Shader behaves.
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


	private:

	};
}

#endif