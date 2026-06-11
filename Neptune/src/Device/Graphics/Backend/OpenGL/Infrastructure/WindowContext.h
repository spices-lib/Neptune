/**
* @file WindowContext.h.
* @brief The WindowContext Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

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
        * @param[in] window Window.
        */
        static SP<WindowContext> Create(Context& context, EInfrastructure e, WindowImplement implement, void* window = nullptr);

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
		void* Handle() const { return m_Window; }

        /**
        * @brief Interface of Make Context Current.
        */
        virtual void MakeContextCurrent() = 0;

		/**
	    * @brief Interface of SwapBuffers.
	    */
	    virtual void SwapBuffers() = 0;
		
    protected:

        void* m_Window = nullptr;   // @brief This Window.
		bool  m_OffScreen = false;  // @brief Is OffScreen.

	};

}

#endif