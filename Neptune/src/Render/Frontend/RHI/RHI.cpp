#include "Pchheader.h"
#include "RHI.h"

namespace Neptune::RHI {

	namespace {
	
		RHIDelegate::Creator s_Creator;
	}

	void RHIDelegate::SetCreator(const RHIDelegate::Creator& fn)
	{
		s_Creator = fn;
	}

	const RHIDelegate::Creator& RHIDelegate::GetCreator()
	{
		return s_Creator;
	}
}