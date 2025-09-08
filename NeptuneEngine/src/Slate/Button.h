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

        Button(std::string slateName)
                : Slate(std::move(slateName))
        {}

        ~Button() override = default;

    private:
        
    };
    
}