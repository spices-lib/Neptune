/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DebugUtilsObject.h"

#ifdef NEPTUNE_DEBUG
#define USE_PIX
#endif

#include <WinPixEventRuntime/pix3.h>

namespace Neptune::Direct3D11 {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::SetHandle(Unit::UserDefinedAnnotation::Handle handle)
	{
		NEPTUNE_PROFILE_ZONE

		m_UserDefinedAnnotation.SetHandle(handle);
		
		DEBUGUTILS_SETOBJECTNAME(m_UserDefinedAnnotation, ToString())
	}

	void DebugUtilsObject::BeginLabel(const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		m_UserDefinedAnnotation.GetHandle()->BeginEvent(StringLibrary::CharToWChar(caption.c_str()).c_str());
	}

	void DebugUtilsObject::EndLabel() const
	{
		NEPTUNE_PROFILE_ZONE

		m_UserDefinedAnnotation.GetHandle()->EndEvent();
	}

	void DebugUtilsObject::InsertLabel(const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		m_UserDefinedAnnotation.GetHandle()->SetMarker(StringLibrary::CharToWChar(caption.c_str()).c_str());
	}
	
}

#endif