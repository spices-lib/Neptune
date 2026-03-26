#include "Pchheader.h"
#include "DescriptorList.h"

namespace Neptune::RHI {

	namespace {
	
		constexpr uint32_t EngineInputSet = 0;
		constexpr uint32_t BineLessTextureSet = 1;

		RHIDescriptorList::Impl* s_SharedDescriptorList = nullptr;
	}
	
	void DescriptorList::SetSharedLayout()
	{
		s_SharedDescriptorList = m_Impl.get();
	}

	RHIDescriptorList::Impl* DescriptorList::GetSharedImpl()
	{
		return s_SharedDescriptorList;
	}
}