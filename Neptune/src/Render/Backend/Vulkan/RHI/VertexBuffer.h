#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include "Render/Frontend/RHI/VertexBuffer.h"

namespace Neptune::Vulkan {

	class VertexBuffer : public ContextAccessor, public RHI::RHIVertexBuffer::Impl
	{
	public:

		VertexBuffer(Context& context) : ContextAccessor(context) {}
		~VertexBuffer() override = default;

	private:

		Unit::Buffer m_Buffer;
	};
}