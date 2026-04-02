/**
* @file SlateBackend.h.
* @brief The SlateBackend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Slate/Frontend/SlateFrontend.h"

namespace Neptune::ImGui {

	class SlateBackend : public SlateFrontend
	{
	public:

        /**
        * @brief Constructor Function.
        */
        SlateBackend() = default;

        /**
        * @brief Destructor Function.
        */
		~SlateBackend() = default;

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


	};

}