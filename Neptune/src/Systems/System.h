/**
* @file System.h.
* @brief The System Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    /**
    * @brief System Class.
    * This class defines the System behaves.
    */
    class System : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        System() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~System() override = default;

        /**
        * @brief Interface of system initialize.
        */
        virtual void OnSystemInitialize() = 0;

        /**
        * @brief Interface of system shutdown.
        */
        virtual void OnSystemShutDown() = 0;

        /**
        * @brief Interface of system tick run.
        */
        virtual void Tick() = 0;

    };
}