/**
* @file SlateBackend.h.
* @brief The SlateBackend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Slate/Frontend/SlateFrontend.h"

namespace Neptune::imgui {

    class RenderInterface;
    class WindowInterface;

    /**
    * @brief imgui::SlateBackend Class.
    * This class defines the imgui::SlateBackend behaves.
    */
	class SlateBackend : public SlateFrontend
	{
	public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] renderBackend RenderBackendEnum.
        * @param[in] windowImpl WindowImplement.
        */
        SlateBackend(RenderBackendEnum renderBackend, WindowImplement windowImpl);

        /**
        * @brief Destructor Function.
        */
		~SlateBackend() override = default;

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
		void OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const override;

        /**
        * @brief Interface of ShutDown.
        */
		void OnShutDown() const override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() const override;

		/**
		* @brief Interface of On Layout.
		*/
		void OnLayout() const override;
		
        /**
        * @brief Interface of End a frame.
        */
        void EndFrame() const override;

		/**
		* @brief Interface of Render a frame.
		* 
		* @param[in] payload RenderFrontend Payload.
		*/
		void RenderFrame(void* payload = nullptr) const override;

	private:

        SP<RenderInterface> m_RenderInterface;         // @brief render backend interface.
        SP<WindowInterface> m_WindowInterface;         // @brief window backend interface.

        RenderBackendEnum m_RenderBackendEnum;         // @brief RenderBackendEnum.
        WindowImplement   m_WindowImplement;           // @brief WindowImplement.
	};

}