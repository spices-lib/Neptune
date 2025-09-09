/**
* @file Level.h.
* @brief The Level Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {
    
    class Level
    {
    public:
        
        Level() = default;
        virtual ~Level() = default;

        const std::string& GetName() const { return m_Name; }

    private:

        std::string m_Name;
    
    };
    
}