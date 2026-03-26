#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Shader.h"
#include "Render/Frontend/RHI/Shader.h"

namespace Neptune::Vulkan {

	class Shader : public ContextAccessor, public RHI::RHIShader::Impl
	{
	public:

		Shader(Context& context) : ContextAccessor(context) {}
		~Shader() override = default;

		const VkShaderModule& Handle() const { return m_Shader.GetHandle(); }

		void SetSource(const std::vector<uint8_t>& source) override;

		void SetName(const std::string& name) override;

	private:

		Unit::Shader m_Shader;
	};
}