/**
* @file SlateFrontend.h.
* @brief The SlateFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Frontend/Enum.h"
#include "Window/Enum.h"

namespace Neptune {

    /**
    * @brief SlateFrontend Class.
    * This class defines the SlateFrontend behaves.
    */
	class SlateFrontend : public NonCopyable
	{
    public:

        /**
        * @brief Create Slate Frontend.
        *
        * @param[in] slateBackend SlateBackendEnum.
        * @param[in] renderBackend RenderBackendEnum.
        * @param[in] windowImpl WindowImplement.
        * 
        * @return Returns Slate Frontend pointer.
        */
        static SP<SlateFrontend> Create(SlateBackendEnum slateBackend, RenderBackendEnum renderBackend, WindowImplement windowImpl);

	public:

        /**
        * @brief Destructor Function.
        */
		~SlateFrontend() override = default;

        /**
        * @brief Interface of Initialize.
        */
		virtual void OnInitialize() = 0;

        /**
        * @brief Interface of ShutDown.
        */
		virtual void OnShutDown() = 0;

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() = 0;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() = 0;

    protected:

        /**
        * @brief Constructor Function.
        *
        * @param[in] backend RenderBackendEnum.
        */
        SlateFrontend(SlateBackendEnum backend) : m_SlateBackendEnum(backend) {}

	private:

        SlateBackendEnum  m_SlateBackendEnum;         // @brief SlateBackendEnum.
	};

}