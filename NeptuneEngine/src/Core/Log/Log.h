/**
* @file Log.h
* @brief The Log Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/NonCopyable.h"

#include <iostream>
#include <memory.h>

namespace Neptune {

    /**
    * @brief Log Class defines log behaves.
    */
    class Log : public NonCopyable
    {
    public:
        
        /**
        * @brief Get this instance.
        * 
        * @return Returns this instance.
        */
        static std::shared_ptr<Log> Get();

        /**
        * @brief Reset this instance.
        */
        static void Reset();

    public:

        /**
        * @brief Constructor Function.
        */
        Log() = default;

        /**
        * @brief Destructor Function.
        */
        ~Log() override = default;

        virtual void CoreTrace   (const std::string& msg) = 0;
        virtual void CoreInfo    (const std::string& msg) = 0;
        virtual void CoreWarn    (const std::string& msg) = 0;
        virtual void CoreError   (const std::string& msg) = 0;
        virtual void CoreCritical(const std::string& msg) = 0;

        virtual void ClientTrace   (const std::string& msg) = 0;
        virtual void ClientInfo    (const std::string& msg) = 0;
        virtual void ClientWarn    (const std::string& msg) = 0;
        virtual void ClientError   (const std::string& msg) = 0;
        virtual void ClientCritical(const std::string& msg) = 0;

        /**
        * @brief Get Initialized state.
        * 
        * @return Returns Initialized state.
        */
        bool IsInitialized() const { return m_IsInitialized; }

    protected:

        /**
        * @brief Boolean of Initialize state.
        */
        bool m_IsInitialized = false;
    };
}

#ifdef NEPTUNE_DEBUG

// Core log macros
#define NEPTUNE_CORE_TRACE(...)    { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreTrace      (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_INFO(...)     { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreInfo       (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_WARN(...)     { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreWarn       (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_ERROR(...)    { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreError      (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_CRITICAL(...) { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->CoreCritical   (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }

// Client log macro
#define NEPTUNE_TRACE(...)         { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->ClientTrace    (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_INFO(...)          { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->ClientInfo     (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_WARN(...)          { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->ClientWarn     (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_ERROR(...)         { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->ClientError    (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CRITICAL(...)      { if(auto logPtr = Neptune::Log::Get(); logPtr->IsInitialized()) { logPtr->ClientCritical (__VA_ARGS__); } else { std::cout << __VA_ARGS__ << std::endl; } }

#endif // NEPTUNE_DEBUG

#ifdef NEPTUNE_RELEASE

// Core log macros
#define NEPTUNE_CORE_TRACE(...)
#define NEPTUNE_CORE_INFO(...)
#define NEPTUNE_CORE_WARN(...)
#define NEPTUNE_CORE_ERROR(...)
#define NEPTUNE_CORE_CRITICAL(...)

// Client log macros
#define NEPTUNE_TRACE(...)
#define NEPTUNE_INFO(...)
#define NEPTUNE_WARN(...)
#define NEPTUNE_ERROR(...)
#define NEPTUNE_CRITICAL(...)

#endif // NEPTUNE_RELEASE