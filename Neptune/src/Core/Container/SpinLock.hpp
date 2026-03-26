/**
* @file SpinLock.hpp.
* @brief The SpinLock Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <mutex>

namespace Neptune {

    /**
    * @brief Spin Lock.
    */
    class SpinLock
    {
    private:

        /**
        * @brief Spin Lock atomic flag.
        */
        std::atomic_flag m_Flag = ATOMIC_FLAG_INIT;

    public:

        /**
        * @brief Constructor Function.
        */
        SpinLock() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~SpinLock() = default;

        /**
        * @brief Copy Constructor Function.
        *
        * @note This Class not allowed copy behaves.
        */
        SpinLock(const SpinLock&) = delete;

        /**
        * @brief Copy Assignment Operation.
        *
        * @note This Class not allowed copy behaves.
        */
        SpinLock& operator=(const SpinLock&) = delete;

        /**
        * @brief Get Lock.
        */
        void Lock()
        {
            while (m_Flag.test_and_set(std::memory_order_acquire)) {}
        }

        /**
        * @brief Release Lock.
        */
        void UnLock()
        {
            m_Flag.clear(std::memory_order_release);
        }

    };

}
