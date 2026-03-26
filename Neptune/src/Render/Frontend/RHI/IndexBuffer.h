#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {
	
	using RHIIndexBuffer = RHI<ERHI::IndexBuffer>;

	template<>
	class RHIIndexBuffer::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;
	};

	class IndexBuffer : public RHIIndexBuffer
	{
	public:

		IndexBuffer() = default;
		~IndexBuffer() override = default;

	};
}