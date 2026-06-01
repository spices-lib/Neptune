/**
* @file RenderDelegate.h.
* @brief The RenderDelegate Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Delegate/DelegateBasic.h"

namespace Neptune {

    DELEGATE_ONE_PARAM(DrawSlate, void*)

    /**
    * @brief Delegate for RenderFrontend.
    */
    struct RenderDelegate
    {
        DelegateDrawSlate onDrawSlate;      // @brief Delegate of DrawSlate.
    };
    
}