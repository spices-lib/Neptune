/**
* @file SlateRegister.h.
* @brief The SlateRegister Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

// Slate Specific Class Header.
#include "Slate/Imgui/ImguiConsole.h"
#include "Slate/Imgui/ViewPort/ImguiViewport.h"
#include "Slate/Imgui/MainMenu/ImguiMainMenu.h"
#include "Slate/Imgui/ViewPort/ImguiGizmos.h"

// STL Header
#include <memory>
#include <vector>
#include <any>
#include <sstream>

namespace Neptune {

	/**
	* @brief This Class is the manager of all slate, it keeps all slate handle.
	*/
	class SlateRegister
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		SlateRegister() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~SlateRegister() = default;

		/**
		* @brief Copy Constructor Function.
		* @note This Class not allowed copy behaves.
		*/
		SlateRegister(const SlateRegister&) = delete;

		/**
		* @brief Copy Assignment Operation.
		* @note This Class not allowed copy behaves.
		*/
		SlateRegister& operator=(const SlateRegister&) = delete;

		/**
		* @brief This function registry slate instance.
		* @tparam T Slate specific type.
		* @param[in] isPrimary Is this slate's render function is called by register or owner.
		* @param[in] panelName The slate name.
		* @return Returns the shared pointer of T.
		*/
		template<typename T, typename ... Args>
		std::shared_ptr<T> Register(bool isPrimary, const std::string& panelName, Args&& ... args);

		/**
		* @note This function is not in use now.
		* @param[in] ts TimeStep.
		*/
		void OnUpdate(TimeStep& ts) const;

		/**
		*  @brief This function is called on SlateRenderer::Render.
		*/
		void OnRender() const;

		/**
		* @brief This function will be called on global Event function pointer is called.
		* @param[in] event The Specific Event Type.
		*/
		void OnEvent(Event& event);

		/**
		* @breif Get Viewport Slate.
		* @return Returns the shared pointer of ImguiViewport.
		* @todo remove this api.
		*/
		std::shared_ptr<ImguiViewport> GetViewPort();

		/**
		* @brief Get Slate by name.
		* @param[in] name Slate name.
		* @reutrn Returns Slate instance.
		*/
		std::shared_ptr<ImguiSlate> GetSlate(const std::string& name);

	private:
		
		/**
		* @brief The container of all slate handle.
		*/
		std::unordered_map<std::string, std::shared_ptr<ImguiSlate>> m_SlatesEventContainer;

		/**
		* @brief The container of all slate handle.
		*/
		std::unordered_map<std::string, std::shared_ptr<ImguiSlate>> m_SlatesRenderContainer;
	};

	template<typename T, typename ...Args>
	inline std::shared_ptr<T> SlateRegister::Register(bool isPrimary, const std::string& panelName, Args && ...args)
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Not allow registy repeat.
		*/
		if (m_SlatesEventContainer.find(panelName) != m_SlatesEventContainer.end())
		{
			std::stringstream ss;
			ss << panelName << " Slate already register, please check your code again.";

			NEPTUNE_CORE_ERROR(ss.str());
		}

		/**
		* @breif Instance T and store it.
		*/
		std::shared_ptr<T> _T = std::make_shared<T>(panelName, FrameInfo::Get(), std::forward<Args>(args)...);
		m_SlatesEventContainer[panelName] = _T;

		if(isPrimary) m_SlatesRenderContainer[panelName] = _T;

		return _T;
	}
}