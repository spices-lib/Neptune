/**
* @file Document.h.
* @brief The Document Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    /**
    * @brief Document Class.
    * This class defines the Document behaves.
    */
    class Document : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Document() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Document() override = default;

    protected:

        std::string m_ActivePage;
        void* m_Data;
    };
}