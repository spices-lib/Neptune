/**
* @file SlateRegister.cpp.
* @brief The SlateRegister Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SlateRegister.h"
#include "Core/Thread/ThreadPoolBasic.h"
#include "Core/Event/KeyEvent.h"

namespace Neptune {

	void SlateRegister::OnUpdate(TimeStep& ts) const
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Iter hash map.
		*/
		for (auto& pair : m_SlatesEventContainer)
		{
			pair.second->OnUpdate(ts);
		}
	}

	void SlateRegister::OnRender() const
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Iter hash map.
		*/
		for (auto& pair : m_SlatesRenderContainer)
		{
			pair.second->OnRender();
		}
	}

	void SlateRegister::OnEvent(Event& event)
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Iter hash map.
		*/
		for (auto& pair : m_SlatesEventContainer)
		{
			pair.second->OnEvent(event);
		}
	}

	std::shared_ptr<ImguiViewport> SlateRegister::GetViewPort()
	{
		NEPTUNE_PROFILE_ZONE;

		return std::static_pointer_cast<ImguiViewport>(m_SlatesRenderContainer["ViewPort"]);
	}

	std::shared_ptr<ImguiSlate> SlateRegister::GetSlate(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE;

		if (m_SlatesEventContainer.find(name) != m_SlatesEventContainer.end())
		{
			return m_SlatesEventContainer[name];
		}

		return nullptr;
	}
}