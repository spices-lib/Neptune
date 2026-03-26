#pragma once
#include "Core/Core.h"
#include <filesystem>

namespace Neptune {

	namespace RHI {
	
		class Shader;
	}

	enum class ShaderStage : uint8_t 
	{
		Vertex = 0,
		Fragment,

		Count
	};

	class Shader
	{
	public:

		Shader() = default;
		~Shader() = default;

		void SetName(const std::string& name) { m_Name = name; }

		void SetStage(ShaderStage stage) { m_Stage = stage; }

		void SetSource(const std::filesystem::path& path);

		SP<RHI::Shader> GetRHIResource() { return m_RHIResource; }

		ShaderStage GetStage() const { return m_Stage; }

	private:

		std::vector<uint8_t> Compile(const std::string& data);

	private:

		std::string           m_Name;
		SP<RHI::Shader>       m_RHIResource;
		ShaderStage           m_Stage;
		std::filesystem::path m_Path;
	};
}