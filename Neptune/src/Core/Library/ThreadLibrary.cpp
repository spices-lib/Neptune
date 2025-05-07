/**
* @file ThreadLibrary.cpp.
* @brief The ThreadLibrary Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ThreadLibrary.h"
#include "StringLibrary.h"

namespace Neptune {
    
    bool ThreadLibrary::SetThreadName(const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE;
        
        const std::wstring n = StringLibrary::CharToWChar(name.c_str());
        
        HRESULT r = SetThreadDescription(GetCurrentThread(), n.c_str());

        switch (r)
        {
        case S_OK: 
            return true;
        case E_ABORT:
            NEPTUNE_CORE_WARN("Operation aborted")
            return false;
        case E_ACCESSDENIED:
            NEPTUNE_CORE_WARN("General access denied error")
            return false;
        case E_FAIL:
            NEPTUNE_CORE_WARN("Unspecified failure")
            return false;
        case E_HANDLE:
            NEPTUNE_CORE_WARN("Handle that is not valid")
            return false;
        case E_INVALIDARG:
            NEPTUNE_CORE_WARN("One or more arguments are not valid")
            return false;
        case E_NOINTERFACE:
            NEPTUNE_CORE_WARN("No such interface supported")
            return false;
        case E_NOTIMPL:
            NEPTUNE_CORE_WARN("Not implemented")
            return false;
        case E_OUTOFMEMORY:
            NEPTUNE_CORE_WARN("Failed to allocate necessary memory")
            return false;
        case E_POINTER:
            NEPTUNE_CORE_WARN("Pointer that is not valid")
            return false;
        case E_UNEXPECTED:
            NEPTUNE_CORE_WARN("Unexpected failure")
            return false;
        }
        
        return true;
    }
}
