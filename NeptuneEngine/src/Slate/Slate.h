/**
* @file Slate.h.
* @brief The Slate Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune {

    /**
    * @brief This Class defines the basic behaves of specific slate.
    * When we add an new Slate, we need inherit from this.
    */
    class Slate
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] slateName The Slate's name.
        */
        Slate(std::string slateName)
                : m_SlateName(std::move(slateName))
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Slate() = default;

        /**
        * @brief This interface is called on Slate Update.
        */
        virtual void OnTick() = 0;

        /**
        * @brief This interface is called on global event function pointer execute.
        * 
        * @param[in] event Event.
        */
        virtual void OnEvent(Event& event) = 0;

    protected:

        /**
		* @brief This slate's name.
		*/
        std::string m_SlateName;
    };
}
