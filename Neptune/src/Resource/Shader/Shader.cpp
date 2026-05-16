#include "Pchheader.h"
#include "Shader.h"
#include "Render/Frontend/RHI/Shader.h"

#ifdef NP_PLATFORM_WINDOWS

#include <glslc/src/file_includer.h>
#include <libshaderc_util/include/libshaderc_util/file_finder.h>

#endif

namespace Neptune {

#ifdef NP_PLATFORM_WINDOWS
	
	namespace {
	
		shaderc_shader_kind ToShaderCKind(ShaderStage stage)
		{
			switch (stage)
			{
				case ShaderStage::Vertex:   return shaderc_shader_kind::shaderc_vertex_shader;
				case ShaderStage::Fragment: return shaderc_shader_kind::shaderc_fragment_shader;
				default:
				{
					NEPTUNE_CORE_WARN("Unsupported ShaderStage To shaderc_shader_kind.")
					return shaderc_shader_kind::shaderc_glsl_infer_from_source;
				}
			}
		}
	
	}

#endif
	
	void Shader::SetSource(const std::filesystem::path& path)
	{
		
#ifdef NP_PLATFORM_WINDOWS
		
		if (!std::filesystem::exists(path))
		{
			std::stringstream ss;
			ss << "Shader: [ " << path << " ] is not found";

			NEPTUNE_CORE_ERROR(ss.str());

			return;
		}

		m_Path = path;

		std::ifstream stream(m_Path);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		std::vector<uint8_t> spirv = Compile(strStream.str());

		m_RHIResource = CreateSP<RHI::Shader>();
		m_RHIResource->SetSource(spirv);
		m_RHIResource->SetName(m_Name);
		
#endif
		
	}

	std::vector<uint8_t> Shader::Compile(const std::string& data)
	{
		
#ifdef NP_PLATFORM_WINDOWS
		
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		shaderc_util::FileFinder fileFinder;
		fileFinder.search_path().push_back("");

#ifdef PG_DEBUG

		options.SetGenerateDebugInfo();

#endif

		options.SetOptimizationLevel(shaderc_optimization_level_performance);                                             
		options.SetTargetSpirv(shaderc_spirv_version_1_6);
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_4);
		options.SetIncluder(std::make_unique<glslc::FileIncluder>(&fileFinder));

		shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(data, ToShaderCKind(m_Stage), m_Path.generic_string().c_str(), options);
		if (module.GetCompilationStatus() != shaderc_compilation_status_success) 
		{
			std::stringstream ss;
			ss << "Error compiling module: " << module.GetErrorMessage();

			NEPTUNE_CORE_ERROR(ss.str())
			return {};
		}
		
		std::vector<uint32_t> code32 = { module.cbegin(), module.cend() };
		std::vector<uint8_t> spirv{};
		spirv.resize(code32.size() * 4);
		memcpy(spirv.data(), code32.data(), spirv.size());

		return std::move(spirv);
	
#else
		
		return {};
		
#endif
	}

}