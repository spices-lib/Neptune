/**
* @file NativeScript.h.
* @brief The NativeScript Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Scripts/ScriptInterface.h"

namespace Neptune {

    /**
    * @brief Native C++ Script Class.
    */
    class NativeScript : public ScriptInterface
    {
    public:

        /**
        * @brief Constructor Function.
        */
        NativeScript() = default;

        /**
        * @brief Destructor Function.
        */
        ~NativeScript() override = default;
    };
}