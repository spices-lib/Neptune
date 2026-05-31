/**
* @file Blob.cpp.
* @brief The Blob Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Blob.h"

namespace Neptune::Direct3D12::Unit {

	Blob::~Blob()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Blob::CreateBlob(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		Handle errorBlob = nullptr;

		auto result = D3D12SerializeVersionedRootSignature(&desc, &m_Handle, &errorBlob);

		if (FAILED(result))
		{
			DIRECT3D12_CHECK(result)

			if (!errorBlob) return;

			std::stringstream ss;
			ss << errorBlob->GetBufferPointer();

			NEPTUNE_CORE_ERROR(ss.str())
		}
	}

}

#endif