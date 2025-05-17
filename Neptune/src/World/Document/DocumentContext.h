/**
* @file DocumentContext.h.
* @brief The DocumentContext Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Document.h"
#include "DocumentPage.h"

namespace Neptune {

    /**
    * @brief DocumentContext Class.
    * This class defines the DocumentContext behaves.
    */
    class DocumentContext : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DocumentContext() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~DocumentContext() override = default;

    public:

        SP<Document> m_Document;
        SP<DocumentPage> m_Page;
    };
}