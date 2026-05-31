/**
* @file Factory.cpp.
* @brief The Factory Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Factory.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

	Factory::Factory(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	void Factory::Create()
    {
        NEPTUNE_PROFILE_ZONE

#ifdef NEPTUNE_DEBUG

        m_Factory.CreateFactory(DXGI_CREATE_FACTORY_DEBUG);

#else

        m_Factory.CreateFactory(0);

#endif

        DEBUGUTILS_SETOBJECTNAME(m_Factory, ToString())
    }

}

#endif