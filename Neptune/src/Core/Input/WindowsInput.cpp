/**
* @file Input.h.
* @brief The WindowsInput Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace Neptune {
	
	/**
	* @brief Instance a WindowsInput single instance.
	*/
	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(const int& keycode)
	{
		NEPTUNE_PROFILE_ZONE;

        return false;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const int& button)
	{
		NEPTUNE_PROFILE_ZONE;

        return false;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		NEPTUNE_PROFILE_ZONE;

        return {};
	}

	float WindowsInput::GetMouseXImpl()
	{
		NEPTUNE_PROFILE_ZONE;

		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		NEPTUNE_PROFILE_ZONE;

		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}