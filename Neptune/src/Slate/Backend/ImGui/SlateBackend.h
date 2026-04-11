/**
* @file SlateBackend.h.
* @brief The SlateBackend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Slate/Frontend/SlateFrontend.h"

namespace Neptune::imgui {

    class RenderAPIInterface;
    class WindowAPIInterface;

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
        */
		void OnInitialize() override;

        /**
        * @brief Interface of ShutDown.
        */
		void OnShutDown() override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() override;

        /**
        * @brief Interface of End a frame.
        */
        void EndFrame() override;

	private:

        SP<RenderAPIInterface> m_RenderAPIInterface;         // @brief render backend interface.
        SP<WindowAPIInterface> m_WindowAPIInterface;         // @brief window backend interface.
	};

}