/**
* @file GraphicsFrontend.h.
* @brief The GraphicsFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "RHI/RHI.h"
#include "Enum.h"

#include <any>

namespace Neptune {

    /**
    * @brief GraphicsFrontend Class.
    * This class defines the GraphicsFrontend behaves.
    */
    class GraphicsFrontend : public NonCopyable
    {
    public:

        /**
        * @brief Create Graphics Frontend.
        *
        * @param[in] backend GraphicsBackendEnum.
        *
        * @return Returns Graphics Frontend pointer.
        */
        static SP<GraphicsFrontend> Create(GraphicsBackendEnum backend);

    public:

        /**
        * @brief Destructor Function.
        */
        ~GraphicsFrontend() override = default;

        /**
        * @brief Interface of Initialize.
        */
        virtual void OnInitialize() = 0;

        /**
        * @brief Interface of ShutDown.
        */
        virtual void OnShutDown() = 0;

        /**
        * @brief Interface of Wait GraphicsBackend idle.
        */
        virtual void Wait() const = 0;

        /**
        * @brief Interface of CreateRHI.
        * 
        * @param[in] e ERHI.
        * @param[in] payload RHI Payload.
        * 
        * @return Returns RHI::Impl
        */
        virtual std::any CreateRHI(RHI::ERHI e, void* payload) const = 0;

        /**
        * @brief Interface of Access Infrastructure.
        *
        * @return Returns Infrastructure.
        */
        virtual std::unordered_map<std::string, std::any> AccessInfrastructure() const = 0;

    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] backend GraphicsBackendEnum.
        */
        GraphicsFrontend(GraphicsBackendEnum backend) : m_GraphicsBackendEnum(backend) {}

    protected:

        GraphicsBackendEnum m_GraphicsBackendEnum;   // @brief GraphicsBackendEnum.
    };
}