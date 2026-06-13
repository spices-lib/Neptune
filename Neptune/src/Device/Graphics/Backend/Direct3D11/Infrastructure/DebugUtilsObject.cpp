/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "DebugUtilsObject.h"
#include "DeviceContext.h"

namespace Neptune::Direct3D11 {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::Create()
	{
		NEPTUNE_PROFILE_ZONE

		m_UserDefinedAnnotation.CreateUserDefinedAnnotation(GetContext().Get<IDeviceContext>()->Handle());
		
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