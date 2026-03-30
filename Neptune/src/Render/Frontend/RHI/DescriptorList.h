/**
* @file DescriptorList.h.
* @brief The DescriptorList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	using RHIDescriptorList = RHI<ERHI::DescriptorList>;

	/**
	* @brief Specialization of RHIDescriptorList::Impl
	*/
	template<>
	class RHIDescriptorList::Impl
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
		* @brief Interface of Add UniformBuffer.
		* 
		* @param[in] set .
		* @param[in] binding .
		* @param[in] bytes UniformBuffer bytes.
		*/
		virtual void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) = 0;

		/**
		* @brief Interface of Add UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		virtual void AddUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) = 0;

		/**
		* @brief Interface of Update UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] data UniformBuffer data.
		*/
		virtual void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) = 0;

		/**
		* @brief Interface of Update UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		virtual void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) = 0;

		/**
		* @brief Interface of Combine Shared DescriptorList.
		*
		* @param[in] shared RHIDescriptorList::Impl.
		*/
		virtual void CombineSharedLayout(const WP<Impl>& shared) = 0;

		/**
		* @brief Interface of Build DescriptorList.
		*/
		virtual void Build() = 0;
	};

	/**
	* @brief RHI of ERHI::DescriptorList
	*/
	class DescriptorList : public RHIDescriptorList
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		DescriptorList() = default;

		/**
		* @brief Destructor Function.
		*/
		~DescriptorList() override = default;

		/**
		* @brief Set this impl as Shared DescriptorList.
		*/
		void SetSharedLayout() const;

	private:

		/**
		* @brief Get Shared DescriptorList impl.
		* 
		* @return Returns RHIDescriptorList::Impl.
		*/
		const WP<Impl>& GetSharedImpl() const;

	public:

		/**
		* @brief Interface of Add UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] bytes UniformBuffer bytes.
		*/
		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) const { DescriptorList::m_Impl->AddUniformBuffer(set, binding, bytes); }

		/**
		* @brief Interface of Add UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void AddUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) const { DescriptorList::m_Impl->AddUniformTexture(set, binding, renderTarget); }

		/**
		* @brief Interface of Update UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] data UniformBuffer data.
		*/
		void UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data) const { DescriptorList::m_Impl->UpdateUniformBuffer(set, binding, data); }

		/**
		* @brief Interface of Update UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateUniformTexture(uint32_t set, uint32_t binding, SP<class RenderTarget> renderTarget) const { DescriptorList::m_Impl->UpdateUniformTexture(set, binding, renderTarget); }

		/**
		* @brief Interface of Combine Shared DescriptorList.
		*/
		void CombineSharedLayout() { DescriptorList::m_Impl->CombineSharedLayout(GetSharedImpl()); }

		/**
		* @brief Interface of Build DescriptorList.
		*/
		void Build() const { m_Impl->Build(); }

	};
}