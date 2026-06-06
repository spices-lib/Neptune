/**
* @file WindowContext.h.
* @brief The WindowContext Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Window/Enum.h"

namespace Neptune::OpenGL {

    using IWindowContext = IInfrastructure<class WindowContext, EInfrastructure::WindowContext>;

    /**
    * @brief OpenGL::WindowContext Class.
    * This class defines the OpenGL::WindowContext behaves.
    */
	class WindowContext : public Infrastructure
	{
    public:

        /**
        * @brief Factory of Create WindowContext with specific implement.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] implement WindowImplement.
        */
        static SP<WindowContext> Create(Context& context, EInfrastructure e, WindowImplement implement);

    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context Context.
		* @param[in] e EInfrastructure.
        */
        WindowContext(Context& context, EInfrastructure e) : Infrastructure(context, e) {}

        /**
        * @brief Destructor Function.
        */
        ~WindowContext() override = default;

        /**
        * @brief Get WindowContext.
        *
        * @return Returns WindowContext.
        */
        const void* Handle() const { return m_Window; }

        /**
        * @brief Make Context Current.
        */
        virtual void MakeContextCurrent() = 0;

    protected:

        void* m_Window;  // @brief This Window.
	};

}

#endif