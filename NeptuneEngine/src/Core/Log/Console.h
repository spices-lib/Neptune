/**
* @file Console.h
* @brief The Console Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <glm/glm.hpp>

namespace Neptune {

    /**
    * @brief Help data of specific level of information.
    */
    struct InfoLevelHelper
    {
        std::string str;    // @brief Info information.
        std::string level;  // @brief specific level of this information.
        glm::vec4 color;    // @brief specific color of this information.
    };

    /**
    * @brief Console Information Data.
    */
    struct InfoData
    {
        std::queue<InfoLevelHelper> m_TraceLogInfos;    // @brief trace    queue.
        std::queue<InfoLevelHelper> m_InfoLogInfos;     // @brief info     queue.
        std::queue<InfoLevelHelper> m_WarnLogInfos;     // @brief warn     queue.
        std::queue<InfoLevelHelper> m_ErrorLogInfos;    // @brief error    queue.
        std::queue<InfoLevelHelper> m_CriticalLogInfos; // @brief critical queue.

        /**
         * @brief clear console buffer. 
         */
        void Clear()
        {
            NEPTUNE_PROFILE_ZONE

            std::queue<InfoLevelHelper>().swap(m_TraceLogInfos);
            std::queue<InfoLevelHelper>().swap(m_InfoLogInfos);
            std::queue<InfoLevelHelper>().swap(m_WarnLogInfos);
            std::queue<InfoLevelHelper>().swap(m_ErrorLogInfos);
            std::queue<InfoLevelHelper>().swap(m_CriticalLogInfos);
        }
    };

    /**
    * @brief Console Entity Class.
    */
    class Console : public spdlog::sinks::base_sink<std::mutex>
    {
    public:

        /**
        * @brief Registry a console to ConsolePool.
        * 
        * @param[in] name ConsoleName.
        * 
        * @return Returns Registered Console form Pool.
        */
        static std::shared_ptr<Console> Registry(const std::string& name);

    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] maxInfos Maximum Num of Information.
        */
        Console(uint32_t maxInfos = 50);

        /**
        * @brief Destructor Function.
        */
        ~Console() override = default;

        /**
        * @brief Get Console Infos.
        * 
        * @return Returns Console Infos.
        */
        const InfoData& GetInfos() const { return m_InfoData; }

        /**
        * @brief Clear Console Infos.
        */
        void Clear();

        /**
        * @brief Push a Command to Console.
        * 
        * @param[in] cmd Command.
        * @todo Implemented it.
        */
        void Push(const std::string& cmd);

    protected:

        /**
        * @brief Inherited from spdlog, run when a message pushed.
        * 
        * @param[in] msg spdlog message.
        */
        void sink_it_(const spdlog::details::log_msg& msg) override;

        /**
        * @brief Inherited from spdlog, run when spdlog flush.
        */
        void flush_() override { Clear(); }

    protected:

        uint32_t m_MaxInfos;     // @brief Maximum Num of Information's.
        InfoData m_InfoData;     // @brief Console Information.
    };
}