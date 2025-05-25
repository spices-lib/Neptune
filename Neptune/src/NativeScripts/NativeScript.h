/**
* @file NativeScript.h.
* @brief The NativeScript Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune {

    /**
    * @brief Native C++ Script Class.
    */
    class NativeScript
    {
    public:

        /**
        * @brief Constructor Function.
        */
        NativeScript() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~NativeScript() = default;

        /**
        * @brief This interface defines the behave on specific component tick every frame.
        */
        virtual void OnTick() = 0;

        /**
        * @brief This interface defines the behave on specific component event happened.
        * @param[in] e Event.
        */
        virtual void OnEvent(Event& e) = 0;
    };
}