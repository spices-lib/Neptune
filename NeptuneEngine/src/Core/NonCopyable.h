/**
* @file NonCopyable.h.
* @brief NonCopyable Class Definitions.
* @author Spices.
*/

#pragma once

namespace Neptune {

class NonCopyable
{
public:

    /**
    * @brief Constructor Function.
    */
    NonCopyable() = default;

    /**
    * @brief Destructor Function.
    */
    virtual ~NonCopyable() = default;

    /**
    * @brief Copy Constructor Function.
    * 
    * @note This Class not allowed copy behaves.
    */
    NonCopyable(const NonCopyable&) = delete;

    /**
    * @brief Copy Assignment Operation.
    * 
    * @note This Class not allowed copy behaves.
    */
    NonCopyable& operator=(const NonCopyable&) = delete;

};

}