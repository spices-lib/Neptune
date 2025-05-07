/**
* @file WorldEvent.h.
* @brief The WorldEvent Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace Neptune {

	/**
	* @brief This Class is inherited from Event Class.
	* Inherit from it and create specific KeyEvent class. 
	* Called when WorldMarkQuery tick.
	* This Event register by ...
	*/
	class WorldEvent : public Event
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		WorldEvent() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~WorldEvent() override = default;

		/**
		* @brief Specific this Class Category with EventCategoryWorld.
		*/
        virtual int GetCategoryFlags() const override {
            return EventCategoryWorld;
        }
	};

	/**
	* @brief This Class is inherited from Event Class.
	*/
	class MeshAddedWorldEvent : public WorldEvent
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		MeshAddedWorldEvent() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~MeshAddedWorldEvent() override = default;

		/**
		* @brief Serialize this Event Class to string.
		* @return Returns Serialized string.
		*/
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MeshAddedWorldEvent";
			
			return ss.str();
		}

		/**
		* @brief Specific this Class Type with MeshAdded.
		*/
        static EventType GetStaticType() {
            return EventType::MeshAdded;
        } virtual EventType GetEventType() const override {
            return GetStaticType();
        } virtual const char* GetName() const override {
            return "MeshAdded";
        }
	};
}