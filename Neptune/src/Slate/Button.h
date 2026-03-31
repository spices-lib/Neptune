/**
* @file Button.h.
* @brief The Button Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Slate.h"

namespace Neptune {
    
    class Button : public Slate
    {
    public:

        Button(const std::string& slateName)
            : Slate(slateName)
        {}

        ~Button() override = default;

    private:
        
    };
    
}