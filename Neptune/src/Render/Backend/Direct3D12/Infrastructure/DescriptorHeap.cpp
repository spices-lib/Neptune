/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DescriptorHeap.h"
#include "DebugUtilsObject.h"
#include "Device.h"
#include "Render/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {

    DescriptorHeap::DescriptorHeap(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void DescriptorHeap::Create()
    {
        NEPTUNE_PROFILE_ZONE

        D3D12_DESCRIPTOR_HEAP_DESC        desc{};
		desc.Flags                      = GetEInfrastructure() == EInfrastructure::SRVDescriptorHeap ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NumDescriptors             = 4096;
		desc.Type                       = GetDescriptorHeapType();
		desc.NodeMask                   = 0;

        m_DescriptorHeap.CreateDescriptorHeap(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_DescriptorHeap, ToString())
    }

    D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap::GetDescriptorHeapType() const
    {
        switch (GetEInfrastructure())
		{
			case EInfrastructure::RTVDescriptorHeap:		return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			case EInfrastructure::DSVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			case EInfrastructure::SRVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			case EInfrastructure::UAVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			default: return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		}
    }

}

#endif