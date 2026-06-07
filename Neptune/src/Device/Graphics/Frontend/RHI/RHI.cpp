/**
* @file RHI.cpp.
* @brief The RHIDelegate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RHI.h"

namespace Neptune::RHI {

	namespace {
	
		RHIDelegate::Creator s_Creator;    // @brief RHI Creator Functor instance.
	}

	void RHIDelegate::SetCreator(const Creator& fn)
	{
		NEPTUNE_PROFILE_ZONE

		s_Creator = fn;
	}

	const RHIDelegate::Creator& RHIDelegate::GetCreator()
	{
		NEPTUNE_PROFILE_ZONE

		return s_Creator;
	}
}