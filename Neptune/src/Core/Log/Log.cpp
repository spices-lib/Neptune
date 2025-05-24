/**
* @file Log.cpp.
* @brief The Log Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Log.h"
#include "LogImpl.h"

namespace Neptune {

    std::shared_ptr<Log> Log::Get()
    {
        static std::shared_ptr<Log> s_Log = nullptr;

        if(!s_Log)
        {
            s_Log = std::make_shared<LogImpl>();
        }

        NEPTUNE_CORE_INFO("Log Module created.")

        return s_Log;
    }
}