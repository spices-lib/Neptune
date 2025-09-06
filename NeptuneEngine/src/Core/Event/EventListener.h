/**
* @file EventListener.h.
* @brief The EventListener Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

#include <memory.h>

namespace Neptune {

    class EventListener
    {
    public:

        template<typename T>
        static bool Dispatch(Event& event, T* instance);

    public:

        EventListener() : m_ListenedType(EventType::None) {}
        EventListener(EventType type) : m_ListenedType(type) {}
        virtual ~EventListener() = default;

        void AddListenEvent(EventType type)
        {
            //m_ListenedType |= type;
        }

        void RemoveListenEvent(EventType type)
        {
            //m_ListenedType &= ~type;
        }

        bool Dispatch(Event& event)
        {
            /*if(event.GetEventType() & m_ListenedType == 0) {
                return false;
            }*/

            OnEvent(event);

            return true;
        }

        virtual void OnEvent(Event& event) = 0;

    private:

        EventType m_ListenedType;
    };

    template<typename T>
    bool EventListener::Dispatch(Event& event, T* instance)
    {
        if(auto p = dynamic_cast<EventListener*>(instance))
        {
            return p->Dispatch(event);
        }

        return false;
    }

}