/**
* @file DescriptorHeap.h.
* @brief The DescriptorHeap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/DescriptorHeap.h"

namespace Neptune::Direct3D12 {

	using IRTVDescriptorHeap   = IInfrastructure<class DescriptorHeap, EInfrastructure::RTVDescriptorHeap>;
	using IDSVDescriptorHeap   = IInfrastructure<class DescriptorHeap, EInfrastructure::DSVDescriptorHeap>;
	using ISRVDescriptorHeap   = IInfrastructure<class DescriptorHeap, EInfrastructure::SRVDescriptorHeap>;
	using IUAVDescriptorHeap   = IInfrastructure<class DescriptorHeap, EInfrastructure::UAVDescriptorHeap>;

	/**
	* @brief Direct3D12::DescriptorHeap Class.
	* This class defines the Direct3D12::DescriptorHeap behaves.
	*/
	class DescriptorHeap : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		DescriptorHeap(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~DescriptorHeap() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::DescriptorHeap::Handle& Handle() const { return m_DescriptorHeap.GetHandle(); }

	private:

		/**
		* @brief Create CommandQueue.
		*/
		void Create();

		/**
		* @brief Get DescriptorHeapType.
		*
		* @return Returns DescriptorHeapType.
		*/
		D3D12_DESCRIPTOR_HEAP_TYPE GetDescriptorHeapType() const;

	private:

		Unit::DescriptorHeap m_DescriptorHeap;    // @brief This DescriptorHeap.
	};

}

#endif