/**
* @file System.cpp.
* @brief The System Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "System.h"
#include "SystemManager.h"

namespace Neptune {

	System* System::GetSystem(ESystem system) const
	{
		NEPTUNE_PROFILE_ZONE

		return m_Manager->GetSystem(system);
	}

}