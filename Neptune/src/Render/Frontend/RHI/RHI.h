#pragma once
#include "Core/Core.h"
#include <functional>
#include <any>
#include <concepts>

namespace Neptune::RHI {
	
	enum class ERHI : uint8_t
	{
		RenderPass = 0,
		DescriptorList,
		Pipeline,
		Shader,
		RenderTarget,
		VertexBuffer,
		IndexBuffer,
		CmdList,
		CmdList2,
		Decoder,
		OpticalFlow,

		Count
	};

	struct RHIDelegate
	{
		using Creator = std::function<std::any(ERHI, void*)>;

		static void SetCreator(const Creator& fn);

		static const Creator& GetCreator();
	};

	template<ERHI E>
	class RHI
	{
	public:

		class Impl
		{	
		public:

			Impl() = default;
			virtual ~Impl() = default;
		};

	public:

		RHI(void* payload = nullptr)
		{
			if (auto p = std::any_cast<SP<Impl>>(std::invoke(RHIDelegate::GetCreator(), E, payload)))
			{
				m_Impl = p;
			}
			else
			{
				CORE_ERROR("RHI Create with wrong ERHI")
			}
		}

		virtual ~RHI() = default;

		template<typename T>
		SP<T> GetRHIImpl()
		{
			return std::dynamic_pointer_cast<T>(m_Impl);
		}

	protected:

		SP<Impl> m_Impl = nullptr;
	};
}