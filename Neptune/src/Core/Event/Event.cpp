/**
* @file Event.cpp.
* @brief The Event Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "Event.h"

namespace Neptune {

    /**
    * @brief Single instance of Root Event Function Pointer.
    */
    static Event::EventCallbackFn EventCallback;

    Event::EventCallbackFn Event::GetEventCallbackFn()
    {
        return EventCallback;
    }

    void Event::SetEventCallbackFn(const EventCallbackFn& callback)
    {
        EventCallback = callback;
    }
}