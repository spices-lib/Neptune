/**
* @file Shader.h.
* @brief The Shader Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Shader/Shader.h"

namespace Neptune::RHI {
	
	using RHIShader = RHI<ERHI::Shader>;

	/**
	* @brief Specialization of RHIShader::Impl
	*/
	template<>
	class RHIShader::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;

		/**
		* @brief Interface of Set Shader Source.
		* 
		* @param[in] source Shader Source.
		*/
		virtual void SetSource(const std::vector<uint8_t>& source) = 0;

		/**
		* @brief Interface of Set Shader Name.
		*
		* @param[in] name Shader Name.
		*/
		virtual void SetName(const std::string& name) = 0;
	};

	/**
	* @brief RHI of ERHI::Shader
	*/
	class Shader : public RHIShader
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Shader() = default;

		/**
		* @brief Destructor Function.
		*/
		~Shader() override = default;
		
		/**
		* @brief Interface of Set Shader Source.
		*
		* @param[in] source Shader Source.
		*/
		void SetSource(const std::vector<uint8_t>& source) const { RHIShader::m_Impl->SetSource(source); }

		/**
		* @brief Interface of Set Shader Name.
		*
		* @param[in] name Shader Name.
		*/
		void SetName(const std::string& name) const { RHIShader::m_Impl->SetName(name); }
	};
}