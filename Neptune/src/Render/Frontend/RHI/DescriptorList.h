#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	using RHIDescriptorList = RHI<ERHI::DescriptorList>;

	template<>
	class RHIDescriptorList::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) = 0;

		virtual void AddUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) = 0;

		virtual void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) = 0;

		virtual void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) = 0;

		virtual void CombineSharedLayout(RHIDescriptorList::Impl* shared) = 0;

		virtual void Build() = 0;
	};

	class DescriptorList : public RHIDescriptorList
	{
	public:

		DescriptorList() = default;
		~DescriptorList() override = default;

		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) { DescriptorList::m_Impl->AddUniformBuffer(set, binding, bytes); }

		void AddUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) { DescriptorList::m_Impl->AddUniformTexture(set, binding, renderTarget); }

		void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) { DescriptorList::m_Impl->UpdateUniformBuffer(set, binding, data); }

		void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) { DescriptorList::m_Impl->UpdateUniformTexture(set, binding, renderTarget); }

		void SetSharedLayout();

		void CombineSharedLayout() { DescriptorList::m_Impl->CombineSharedLayout(GetSharedImpl()); }

		void Build() const { DescriptorList::m_Impl->Build(); }

		RHIDescriptorList::Impl* GetSharedImpl();
	};
}