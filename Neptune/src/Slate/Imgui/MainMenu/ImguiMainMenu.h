/**
* @file ImguiMainMenu.h
* @brief The ImguiMainMenu Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "../ImguiUtils.h"

namespace Neptune {

	/**
	* @brief Forward Declare.
	*/
	class ImguiFile;

	/**
	* @brief Forward Declare.
	*/
	class ImguiEdit;

	/**
	* @brief Forward Declare.
	*/
	class ImguiWindow;

	/**
	* @brief Forward Declare.
	*/
	class ImguiCreateEntity;

	/**
	* @brief Forward Declare.
	*/
	class ImguiHelp;

	/**
	* @brief The ImguiMainMenu Class.
	* This class defines how to render a main menu.
	*/
	class ImguiMainMenu : public ImguiSlate
	{
	public:

		/**
		* @brief Constructor Function.
		* @param[in] panelName The Slate's name to show.
		* @param[in] frameInfo The Frame Date that in use.
		*/
		ImguiMainMenu(
			const std::string& panelName , 
			FrameInfo&         frameInfo
		);

		/**
		* @brief Destructor Function.
		*/
		virtual ~ImguiMainMenu() override = default;

		/**
		* @brief This interface is called On SlateSystem Update.
		* @param[in] ts TimeStep.
		*/
		virtual void OnUpdate(TimeStep& ts) override {};

		/**
		* @brief This interface is called On SlateRenderer Render.
		*/
		virtual void OnRender() override;

		/**
		* @brief This interface is called On Global Event Function Pointer is called.
		*/
		virtual void OnEvent(Event& event) override;

	private:


	};

}