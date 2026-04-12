/**
* @file ScriptInterface.h.
* @brief The ScriptInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

#include <filesystem>

namespace Neptune {

    /**
    * @brief Script interface Class.
    */
    class ScriptInterface : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        ScriptInterface() = default;

        /**
        * @brief Constructor Function.
        * 
        * @param[in] path script file path.
        */
        ScriptInterface(const std::filesystem::path& path) : m_ScriptPath(path) {};

        /**
        * @brief Destructor Function.
        */
        ~ScriptInterface() override = default;

        /**
        * @brief This interface defines to behave on specific component on construct.
        */
        virtual void OnConstruct() {}

        /**
        * @brief This interface defines to behave on specific component on attached.
        */
        virtual void OnAttached() {}
        
        /**
        * @brief This interface defines the behave on specific component tick every frame.
        */
        virtual void OnTick() {}

        /**
        * @brief This interface defines to behave on specific component on destroy.
        */
        virtual void OnDestroy() {}

        /**
        * @brief This interface defines to behave on specific component on detached.
        */
        virtual void OnDetached() {}
        
        /**
        * @brief This interface defines the behave on specific component event happened.
        * 
        * @param[in] e Event.
        */
        virtual void OnEvent(Event& e) {}

        /**
        * @brief Get script file string.
        * 
        * @return Script file string.
        */
        std::string GetFileString() const { return m_ScriptPath.generic_string(); }

    protected:

        /**
        * @brief Script file path.
        */
        std::filesystem::path m_ScriptPath;
    };
}