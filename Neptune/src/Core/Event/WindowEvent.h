/**
* @file WindowEvent.h.
* @brief The WindowEvent Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace Neptune {

	/**
	* @brief This Class is inherited from Event Class.
	* Called when window resized.
	* This Event register by glfw window.
	*/
	class WindowResizeEvent : public Event
	{
	public:

		/**
		* @brief Constructor Function.
		* @param[in] width New Viewport Size.
		* @param[in] height New Viewport Size.
		*/
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width)
		    , m_Height(height)
		{}

		/**
		* @brief Destructor Function.
		*/
		virtual ~WindowResizeEvent() override = default;

		/**
		* @brief Get New Windows Width.
		* @return Returns New Windows Width.
		*/
		const uint32_t& GetWidth() const { return m_Width; }

		/**
		* @brief Get New Windows Height.
		* @return Returns New Windows Height.
		*/
		const uint32_t& GetHeight() const { return m_Height; }

		/**
		* @brief Serialize this Event Class to string.
		* @return Returns Serialized string.
		*/
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			
			return ss.str();
		}

		/**
		* @brief Specific this Class Type with WindowResize.
		*/
        static EventType GetStaticType() {
            return EventType::WindowResize;
        } virtual EventType GetEventType() const override {
            return GetStaticType();
        } virtual const char* GetName() const override {
            return "WindowResize";
        }

		/**
		* @brief Specific this Class Category with EventCategoryApplication.
		*/
        virtual int GetCategoryFlags() const override {
            return EventCategoryApplication;
        }

	private:

		/**
		* @brief New Windows Width.
		*/
		uint32_t m_Width;

		/**
		* @brief New Windows Height.
		*/
		uint32_t m_Height;
	};

	/**
	* @brief This Class is inherited from Event Class.
	*/
	class WindowCloseEvent : public Event
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		WindowCloseEvent() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~WindowCloseEvent() override = default;
		
		/**
		* @brief Specific this Class Type with WindowClose.
		*/
        static EventType GetStaticType() {
            return EventType::WindowClose;
        } virtual EventType GetEventType() const override {
            return GetStaticType();
        } virtual const char* GetName() const override {
            return "WindowClose";
        }

		/**
		* @brief Specific this Class Category with EventCategoryApplication.
		*/
        virtual int GetCategoryFlags() const override {
            return EventCategoryApplication;
        }
	};

	/**
	* @breif This Class is inherited from Event Class.
	* Called when window resized over.
	* This Event register by VkSwapchain.
	*/
	class WindowResizeOverEvent : public Event
	{
	public:

		/**
		* @brief Constructor Function.
		* @param[in] width New Viewport Size.
		* @param[in] height New Viewport Size.
		*/
		WindowResizeOverEvent(uint32_t width, uint32_t height)
			: m_Width(width)
		    , m_Height(height)
		{}

		/**
		* @brief Destructor Function.
		*/
		virtual ~WindowResizeOverEvent() override = default;

		/**
		* @brief Get New Windows Width.
		* @return Returns New Windows Width.
		*/
		const uint32_t& GetWidth() const { return m_Width; }

		/**
		* @brief Get New Windows Height.
		* @return Returns New Windows Height.
		*/
		const uint32_t& GetHeight() const { return m_Height; }

		/**
		* @brief Serialize this Event Class to string.
		* @return Returns Serialized string.
		*/
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeOverEvent: " << m_Width << ", " << m_Height;
			
			return ss.str();
		}

		/**
		* @brief Specific this Class Type with WindowResizeOver.
		*/
        static EventType GetStaticType() {
            return EventType::WindowResizeOver;
        } virtual EventType GetEventType() const override {
            return GetStaticType();
        } virtual const char* GetName() const override {
            return "WindowResizeOver";
        }

		/**
		* @brief Specific this Class Category with EventCategoryApplication.
		*/
        virtual int GetCategoryFlags() const override {
            return EventCategoryApplication;
        }

	private:

		/**
		* @brief New Windows Width.
		*/
		uint32_t m_Width;

		/**
		* @brief New Windows Height.
		*/
		uint32_t m_Height;
	};
}