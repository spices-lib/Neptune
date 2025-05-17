/**
* @file WebGPURenderBackend.h.
* @brief The WebGPURenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/FrontEnd/RenderFrontEnd.h"

namespace Neptune {

    class WebGPUState;
    class WebGPUInstance;
    class WebGPUDevice;
    class WebGPUSwapChain;
    class WebGPUCommandEncoder;

    /**
    * @brief WebGPURenderBackend Class.
    * This class defines the WebGPURenderBackend behaves.
    */
    class WebGPURenderBackend : public RenderFrontEnd
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        WebGPURenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPURenderBackend();

        virtual void BeginFrame() override;
        virtual void EndFrame() override;
        virtual void RenderFrame() override;

    private:

        SP<WebGPUState>     m_State;
        SP<WebGPUInstance>  m_Instance;
        SP<WebGPUDevice>    m_Device;

        SP<WebGPUCommandEncoder> m_CommandEncoder;
        SP<WebGPUSwapChain> m_SwapChain;
    };
}