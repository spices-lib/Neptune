#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Shader/Shader.h"

namespace Neptune::RHI {
	
	using RHIShader = RHI<ERHI::Shader>;

	template<>
	class RHIShader::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetSource(const std::vector<uint8_t>& source) = 0;

		virtual void SetName(const std::string& name) = 0;
	};

	class Shader : public RHIShader
	{
	public:

		Shader() = default;
		~Shader() override = default;
		
		void SetSource(const std::vector<uint8_t>& source) { RHIShader::m_Impl->SetSource(source); }

		void SetName(const std::string& name) { RHIShader::m_Impl->SetName(name); }
	};
}