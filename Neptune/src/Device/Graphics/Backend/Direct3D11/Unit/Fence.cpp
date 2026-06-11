/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Fence.h"

namespace Neptune::Direct3D11::Unit {

	Fence::~Fence()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();

		CloseHandle(m_Event);
	}

	void Fence::CreateFence(D3D11Device device)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D11_CHECK(device->CreateFence(0, D3D11_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Handle)))

		m_Event = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	}
	
	uint64_t Fence::GetNextWaitValue()
	{
		m_Value = m_Handle->GetCompletedValue() + 1;
		
		return m_Value;
	}

	void Fence::Wait() const
	{
		if (m_Handle->GetCompletedValue() >= m_Value) return;
		
		DIRECT3D11_CHECK(m_Handle->SetEventOnCompletion(m_Value, m_Event))

		WaitForSingleObject(m_Event, INFINITE);
	}
}

#endif