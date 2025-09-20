/**
* @file RenderFrontend.h.
* @brief The RenderFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"

namespace Neptune {

    /**
    * @brief RenderFrontend Class.
    * This class defines the RenderFrontEnd behaves.
    */
    class RenderFrontend : public NonCopyable
    {
    public:

        /**
        * @brief Create Render Frontend.
        *
        * @param[in] backend RenderBackendEnum.
        *
        * @return Returns Render Frontend pointer.
        */
        static SP<RenderFrontend> Create(RenderBackendEnum backend);

    public:

        /**
        * @brief Destructor Function.
        */
        ~RenderFrontend() override = default;

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() = 0;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() = 0;

        /**
        * @brief Interface of Render a frame.
        */
        virtual void RenderFrame() = 0;

    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] backend RenderBackendEnum.
        */
        RenderFrontend(RenderBackendEnum backend) : m_RenderBackendEnum(backend) {}

    protected:

        /**
        * @brief RenderBackendEnum.
        */
        RenderBackendEnum m_RenderBackendEnum;
    };
}