/**
* @file DescriptorList.h.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "DescriptorList.h"

namespace Neptune::RHI {

	namespace {
	
		WP<RHIDescriptorList::Impl> s_SharedDescriptorList;    // @brief Shared DescriptorList.
	}
	
	void DescriptorList::SetSharedLayout() const
	{
		s_SharedDescriptorList = m_Impl;
	}

	const WP<RHIDescriptorList::Impl>& DescriptorList::GetSharedImpl() const
	{
		return s_SharedDescriptorList;
	}
}