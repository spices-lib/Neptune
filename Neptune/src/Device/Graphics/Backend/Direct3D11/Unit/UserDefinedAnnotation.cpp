/**
* @file UserDefinedAnnotation.cpp.
* @brief The UserDefinedAnnotation Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "UserDefinedAnnotation.h"

namespace Neptune::Direct3D11::Unit {

    UserDefinedAnnotation::~UserDefinedAnnotation()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->Release();
    }
    
    void UserDefinedAnnotation::CreateUserDefinedAnnotation(D3D11DeviceContext deviceContext)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D11_CHECK(deviceContext->QueryInterface(IID_PPV_ARGS(&m_Handle)))
    }
    
}

#endif