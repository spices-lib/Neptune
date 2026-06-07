/**
* @file DescriptorList.h.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "DescriptorList.h"

namespace Neptune::RHI {

	namespace {
	
		RHIDescriptorList::Impl* s_SharedDescriptorList = nullptr;    // @brief Shared DescriptorList.
	}
	
	void DescriptorList::SetSharedLayout() const
	{
		s_SharedDescriptorList = m_Impl.get();
	}

	const RHIDescriptorList::Impl* DescriptorList::GetSharedImpl() const
	{
		return s_SharedDescriptorList;
	}
}