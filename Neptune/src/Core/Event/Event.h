/**
* @file Event.h.
* @brief The Event Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/BitSet.hpp"

#include <functional>
#include <sstream>

namespace Neptune {

    /**
    * @brief This enum defines what specific event type is.
    */
    enum class EventType : uint32_t
    {
        /**
        * @brief Window Event.
        */
        WindowClose            = 0,
        WindowResize           = 1,
        WindowResizeOver       = 2,
        WindowFocus            = 3,
        WindowLostFocus        = 4,
        WindowMoved            = 5,

        /**
        * @brief Slate Event.
        */
        SlateResize            = 6,

        /**
        * @brief Key Input Event.
        */
        KeyPressed             = 7,
        KeyReleased            = 8,
        KeyTyped               = 9,

        /**
        * @brief Mouse Input Event.
        */
        MouseButtonPressed     = 10,
        MouseButtonReleased    = 11,
        MouseMoved             = 12,
        MouseScrolled          = 13,

        /**
        * @brief World Event.
        */
        MeshAdded              = 14,

        /**
        * @brief ALL Event.
        */
        ALL                  = 18,
    };

    /**
    * @brief This enum defines what specific event category is.
    */
    enum class EventCategory : uint16_t
    {
        EventCategoryApplication  = 0,    /* @brief Application  */
        EventCategorySlate        = 1,    /* @brief Slate        */
        EventCategoryInput        = 2,    /* @brief Input        */
        EventCategoryKeyboard     = 3,    /* @brief Keyboard     */
        EventCategoryMouse        = 4,    /* @brief Mouse        */
        EventCategoryMouseButton  = 5,    /* @brief MouseButton  */
        EventCategoryWorld        = 6,    /* @brief World        */

        ALL                       = 7
    };

namespace Detail {

    /**
    * @brief Set Event Categories.
    * 
    * @param[in] flags The Event Categories.
    * @param[in] categories The Categories.
    */
    template<typename... T>
    void SetEventCategories(BitSet<EventCategory>& flags, T... categories)
    {
        (flags.Set(categories, true), ...);
    }

}
    
    /**
    * @brief Defines Event type.
    */
    #define EVENT_CLASS_TYPE(type)                                                              \
	static    EventType          GetStaticType()                { return EventType::type; }     \
	virtual   EventType          GetEventType()  const override { return GetStaticType(); }     \
	virtual   const std::string  GetName()       const override { return #type; }

    /**
    * @brief Defines Event category.
    */
    #define EVENT_CLASS_CATEGORY(...)                                        \
	virtual BitSet<EventCategory> GetCategoryFlags() const override          \
    {                                                                        \
        using enum EventCategory;                                            \
                                                                             \
        static BitSet<EventCategory> s_Category;                             \
                                                                             \
        if (s_Category.None())                                               \
        {                                                                    \
             Detail::SetEventCategories(s_Category, __VA_ARGS__);            \
        }                                                                    \
                                                                             \
        return s_Category;                                                   \
    }

    /**
    * @brief Bind Event.
    */
    #define BIND_EVENT_FN(x)                                                 \
	std::bind(&x, this, std::placeholders::_1)

    /**
    * @brief This Class is the basic Event Class.
    * Inherit from it and create specific event class.
    */
    class Event
    {
    public:

        /**
        * @brief Destructor Function.
        */
        virtual ~Event() = default;

        /**
        * @brief Helper type of Function pointer.
        */
        using EventCallbackFn = std::function<void(Event&)>;

        /**
        * @brief Allow EventDispatcher access all data of this.
        */
        friend class EventDispatcher;

        /**
        * @brief Event Information Function, must be implemented by EVENT_CLASS_TYPE and EVENT_CLASS_CATEGORY.
        */
        virtual EventType               GetEventType()           const = 0;
        virtual const std::string       GetName()                const = 0;
        virtual BitSet<EventCategory>   GetCategoryFlags()       const = 0;
        virtual std::string             ToString()               const { return GetName(); }

        /**
        * @brief Judgement if a given category is contained by this event class.
        * 
        * @param[in] category In category.
        * 
        * @return Returns true if given category is contained by this event class.
        */
        [[nodiscard]] bool IsInCategory(EventCategory category) const
        {
            NEPTUNE_PROFILE_ZONE

            return GetCategoryFlags().Test(category);
        }

        /**
        * @brief Get Global Root Event Function Pointer.
        * 
        * @return Returns the Global Root Event Function Pointer.
        */
        static EventCallbackFn GetEventCallbackFn();

        /**
        * @brief Set Global Root Event Function Pointer.
        * 
        * @param[in] callback The Global Root Event Function Pointer.
        * 
        * @note Usually call it once in whole Application lifetime.
        */
        static void SetEventCallbackFn(const EventCallbackFn& callback);

        /**
        * @brief True if this event is handled.
        */
        bool Handled = false;
    };

    /**
    * @brief This Class store a Specific Event type first
    * and Dispatch a event handle function to it.
    */
    class EventDispatcher
    {

        /**
        * @brief Helper type of the function pointer to handle specific event.
        * 
        * @tparam T Specific Event Class.
        * 
        * @return Returns true if needs block event chain.
        */
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] event Specific Event reference.
        */
        EventDispatcher(Event& event)
                :m_Event(event)
        {}

        /**
        * @brief Dispatch the specific Event handle function pointer to Event Class.
        * 
        * @param[in] func Specific Event handle function.
        * 
        * @return Returns true if execute function pointer.
        */
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            NEPTUNE_PROFILE_ZONE

            /**
            * @brief If Specific Event handle function takes the same type with Stored Event type,
            * will execute the function pointer.
            */
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(*static_cast<T*>(&m_Event));

                return true;
            }

            return false;
        }

    private:

        /**
        * @brief Store the specific Event reference.
        */
        Event& m_Event;
    };

    /**
    * @brief Serialize Event Type.
    */
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}