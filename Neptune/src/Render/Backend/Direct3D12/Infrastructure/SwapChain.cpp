/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "SwapChain.h"
#include "Factory.h"
#include "Queue.h"
#include "DebugUtilsObject.h"
#include "SwapChain/GLFW/SwapChain.h"

namespace Neptune::Direct3D12 {

	SP<SwapChain> SwapChain::Create(Context& context, EInfrastructure e, uint32_t count, WindowImplement implement, void* window)
    {
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
            case WindowImplement::GLFW:            return CreateSP<GLFW::SwapChain>(context, e, count, window);
            default:
            {
                NEPTUNE_CORE_ERROR("SwapChain Create with WindowImplement that not supported.")
                return nullptr;
            }
        }
    }

    void SwapChain::Create(DXGI_SWAP_CHAIN_DESC1& desc, uint32_t count, HWND hwnd)
    {
		const auto factory = GetContext().Get<IFactory>()->Handle();

		factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &m_AllowTearing, sizeof(m_AllowTearing));

		desc.AlphaMode                     = DXGI_ALPHA_MODE_UNSPECIFIED;
		desc.BufferCount                   = count;
		desc.BufferUsage                   = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.Flags                         = m_AllowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
		desc.Format                        = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count              = 1;
		desc.SampleDesc.Quality            = 0;
		desc.Scaling                       = DXGI_SCALING_STRETCH;
		desc.SwapEffect                    = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.Stereo                        = false;

        m_SwapChain = CreateSP<Unit::SwapChain>();
		m_SwapChain->CreateSwapChain(factory, GetContext().Get<IGraphicQueue>()->Handle(), desc, hwnd);
		DEBUGUTILS_SETOBJECTNAME(*m_SwapChain, ToString())

		for (size_t i = 0; i < count; ++i)
		{
			// rendertargetview
		}
    }

	bool SwapChain::Present() const
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(m_SwapChain->GetHandle()->Present(0, m_AllowTearing ? DXGI_PRESENT_ALLOW_TEARING : 0))

		return true;
	}
}

#endif