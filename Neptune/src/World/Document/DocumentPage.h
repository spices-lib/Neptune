/**
* @file DocumentPage.h.
* @brief The DocumentPage Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    class Document;

    /**
    * @brief DocumentPage Class.
    * This class defines the DocumentPage behaves.
    */
    class DocumentPage : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DocumentPage() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~DocumentPage() override = default;

        void OnPreLoad(Document* document);
        void OnDeactivate();

    };
}