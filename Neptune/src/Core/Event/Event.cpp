/**
* @file Event.cpp.
* @brief The Event Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "Event.h"

namespace Neptune {
    
    namespace {
        
        Event::EventCallbackFn S_EventCallback;        // @brief Single instance of Root Event Function Pointer.
    }
    
    Event::EventCallbackFn Event::GetEventCallbackFn()
    {
        NEPTUNE_PROFILE_ZONE

        return S_EventCallback;
    }

    void Event::SetEventCallbackFn(const EventCallbackFn& callback)
    {
        NEPTUNE_PROFILE_ZONE

        S_EventCallback = callback;
    }
}