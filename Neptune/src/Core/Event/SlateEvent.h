/**
* @file SlateEvent.h.
* @brief The SlateEvent Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace Neptune {

	/**
	* @brief This Class is inherited from Event Class.
	* Called by Viewport Resize.
	*/
	class SlateResizeEvent : public Event
	{
	public:

		/**
		* @brief Constructor Function.
		* @param[in] width New Viewport Size.
		* @param[in] height New Viewport Size.
		*/
		SlateResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width)
		    , m_Height(height)
		{}

		/**
		* @brief Destructor Function.
		*/
		virtual ~SlateResizeEvent() override = default;

		/**
		* @brief Get New Viewport Width.
		* @return Returns the New Viewport Width.
		*/
		const uint32_t& GetWidth() const { return m_Width; }

		/**
		* @brief Get New Viewport Height.
		* @return Returns the New Viewport Width.
		*/
		const uint32_t& GetHeight() const { return m_Height; }

		/**
		* @brief Serialize this Event Class to string.
		* @return Returns Serialized string.
		*/
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "SlateResizeEvent: " << m_Width << ", " << m_Height;
			
			return ss.str();
		}

		/**
		* @brief Specific this Class Type with SlateResize.
		*/
        static EventType GetStaticType() {
            return EventType::SlateResize;
        } virtual EventType GetEventType() const override {
            return GetStaticType();
        } virtual const char* GetName() const override {
            return "SlateResize";
        }

		/**
		* @brief Specific this Class Category with EventCategorySlate.
		*/
        virtual int GetCategoryFlags() const override {
            return EventCategorySlate;
        }

	private:

		/**
		* @brief New Viewport Width.
		*/
		uint32_t m_Width;

		/**
		* @brief New Viewport Height.
		*/
		uint32_t m_Height;
	};
}