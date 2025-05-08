/**
* @file WorldPickIDQuerier.cpp.
* @brief The WorldPickIDQuerier & NativeScriptRegister Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WorldPickIDQuerier.h"
#include "Systems/SlateSystem.h"
#include "Slate/Imgui/ViewPort/ImguiViewport.h"
#include "Core/Input/MouseButtonCodes.h"
#include "Core/Input/Input.h"
#include "Core/Input/KeyCodes.h"
#include "World/Entity.h"
#include "World/World/World.h"

namespace Neptune {

	void WorldPickIDQuerier::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(WorldPickIDQuerier::OnMouseButtonPressed));
	}

	bool WorldPickIDQuerier::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		NEPTUNE_PROFILE_ZONE;
		
		/**
		* @brief The first frame, we will not get register pointer.
		*/
		if (!SlateSystem::GetRegister()) return false;

		/**
		* @brief Get viewport.
		*/
		if (!m_ViewPort.lock()) m_ViewPort = SlateSystem::GetRegister()->GetViewPort();

		if (!m_ViewPort.lock()->IsHovered() || m_ViewPort.lock()->GetGizmo()->IsOver()) return false;

		if (m_ViewPort.lock()->GetMousePosInViewport().first < 0                              ||
			m_ViewPort.lock()->GetMousePosInViewport().first > m_ViewPort.lock()->GetPanelSize().x   ||
			m_ViewPort.lock()->GetMousePosInViewport().second < 0                             ||
			m_ViewPort.lock()->GetMousePosInViewport().second > m_ViewPort.lock()->GetPanelSize().y
			)
		{
			return false;
		}

		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			/**
			* @brief Add pick.
			*/
			if (Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift))
			{

			}

			/**
			* @breif Sub pick.
			*/
			else if (Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl))
			{

			}

			/**
			* @breif Single Select.
			*/
			else
			{

			}
		}

		/**
		* @breif Cancle Select.
		*/
		else if (e.GetMouseButton() == Mouse::ButtonRight)
		{
			FrameInfo::Get().m_PickEntityID.clear();

			NEPTUNE_CORE_TRACE("Cancel all selected entity")
		}

		return false;
	}
}