/**
* @file Log.cpp.
* @brief The Log Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "LogImpl.h"
#include "Console.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <time.h>

namespace Neptune {

    LogImpl::LogImpl() : Log()
    {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l] %v");
        //spdlog::flush_every(std::chrono::seconds(5));

        auto max_size = 1048576 * 5;
        auto max_files = 3;

        // Log/Log.log file.
        /*time_t timep;
        tm* p;

        auto error = time(&timep);
        p = localtime(&timep);

        std::stringstream ss;
        ss <<
       SPICES_CONSOLElOGFILE_PATH <<
       p->tm_year + 1900 <<
       p->tm_mon  + 1 <<
       p->tm_mday << "_" <<
       p->tm_hour <<
       p->tm_min  <<
       p->tm_sec  <<
       ".log";*/

        /*const auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(ss.str(), max_size, max_files);
        file_sink->set_level(spdlog::level::trace);*/

        // console log.
        const auto ide_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        ide_console_sink->set_level(spdlog::level::trace);

        //const auto console_sink = Console::Registry("Console", ss.str());

        // console slate log.
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(ide_console_sink);
        //sinks.push_back(file_sink);
        //sinks.push_back(console_sink);

        m_CoreLogger = std::make_shared<spdlog::logger>("Engine", begin(sinks), end(sinks));
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = std::make_shared<spdlog::logger>("Game", begin(sinks), end(sinks));
        m_ClientLogger->set_level(spdlog::level::trace);

        m_IsInitialized = true;
    }

    LogImpl::~LogImpl ()
    {
        m_IsInitialized = false;

        m_CoreLogger.reset();
        m_ClientLogger.reset();
        spdlog::drop_all();
    }

    void LogImpl::CoreTrace   (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->trace(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::CoreInfo    (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->info(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::CoreWarn    (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->warn(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::CoreError   (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->error(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::CoreCritical(const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->critical(ss.str());
        printf(ss.str().c_str());
    }

    void LogImpl::ClientTrace   (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->trace(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::ClientInfo    (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->info(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::ClientWarn    (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->warn(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::ClientError   (const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->error(ss.str());
        printf(ss.str().c_str());
    }
    void LogImpl::ClientCritical(const std::string& msg)
    {
        std::stringstream ss;
        ss << msg << "\n";

        m_CoreLogger->critical(ss.str());
        printf(ss.str().c_str());
    }
}