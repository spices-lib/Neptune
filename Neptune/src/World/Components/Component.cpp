/**
* @file Component.cpp.
* @brief The Component Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Component.h"
#include "World/Entity.h"
#include "Slate/Imgui/ImguiHelper.h"

namespace Neptune {

	void Component::OnComponentAdded(const entt::entity& entity)
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Set m_Owner Variable.
		*/
		m_Owner = entity;
	}
}