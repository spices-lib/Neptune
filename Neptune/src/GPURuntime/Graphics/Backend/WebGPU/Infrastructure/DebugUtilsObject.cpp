/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

	void DebugUtilsObject::BeginLabel(const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DebugUtilsObject::EndLabel() const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void DebugUtilsObject::InsertLabel(const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

}

#endif