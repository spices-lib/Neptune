/**
* @file SandBoxDocument.h.
* @brief The SandBoxDocument Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <World/Document/Document.h>

namespace Neptune {

    /**
    * @brief Document Class.
    * This class defines the Document behaves.
    */
    class SandBoxDocument : public Document
    {
    public:

        /**
        * @brief Constructor Function.
        */
        SandBoxDocument() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~SandBoxDocument() override = default;
    };
}