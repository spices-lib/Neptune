/**
* @file Log.cpp.
* @brief The Log Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Log.h"
#include "LogImpl.h"

namespace Neptune {

    static std::shared_ptr<Log> s_Log = nullptr;

    std::shared_ptr<Log> Log::Get()
    {
        if(!s_Log)
        {
            s_Log = std::make_shared<LogImpl>();
        }

        return s_Log;
    }

    void Log::Reset()
    {
        s_Log.reset();
    }

}