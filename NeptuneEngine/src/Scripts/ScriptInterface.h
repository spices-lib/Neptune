/**
* @file ScriptInterface.h.
* @brief The ScriptInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune {

    /**
    * @brief Script interface Class.
    */
    class ScriptInterface
    {
    public:

        /**
        * @brief Constructor Function.
        */
        ScriptInterface() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~ScriptInterface() = default;

        /**
        * @brief This interface defines the behave on specific component on construct.
        */
        virtual void OnConstruct() = 0;
        
        /**
        * @brief This interface defines the behave on specific component tick every frame.
        */
        virtual void OnTick() = 0;

        /**
        * @brief This interface defines the behave on specific component on destroy.
        */
        virtual void OnDestroy() = 0;
        
        /**
        * @brief This interface defines the behave on specific component event happened.
        * 
        * @param[in] e Event.
        */
        virtual void OnEvent(Event& e) = 0;
    };
}