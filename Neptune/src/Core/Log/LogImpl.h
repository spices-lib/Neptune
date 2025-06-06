/**
* @file LogImpl.h
* @brief The LogImpl Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/NonCopyable.h"
#include "Log.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // This Macro must be defined.
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Neptune {

    /**
    * @brief Log Class defines log behaves.
    */
    class LogImpl : public Log
    {
    public:

        static std::shared_ptr<Log> Get();

    public:

        /**
        * @brief Constructor Function.
        */
        LogImpl();

        /**
        * @brief Destructor Function.
        */
        virtual ~LogImpl() override;

        virtual void CoreTrace   (const std::string& msg) override;
        virtual void CoreInfo    (const std::string& msg) override;
        virtual void CoreWarn    (const std::string& msg) override;
        virtual void CoreError   (const std::string& msg) override;
        virtual void CoreCritical(const std::string& msg) override;

        virtual void ClientTrace   (const std::string& msg) override;
        virtual void ClientInfo    (const std::string& msg) override;
        virtual void ClientWarn    (const std::string& msg) override;
        virtual void ClientError   (const std::string& msg) override;
        virtual void ClientCritical(const std::string& msg) override;

    private:

        /**
        * @brief Engine Stage Logger.
        */
        std::shared_ptr<spdlog::logger> m_CoreLogger;

        /**
        * @brief Game Stage Logger.
        */
        std::shared_ptr<spdlog::logger> m_ClientLogger;
    };
}