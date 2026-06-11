/**
* @file WindowContext.h.
* @brief The WindowContext Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/WindowContext.h"

namespace Neptune::OpenGL::GLFW {

	/**
	* @brief OpenGL::GLFW::WindowContext Class.
	* This class defines the OpenGL::GLFW::WindowContext behaves.
	*/
	class WindowContext : public OpenGL::WindowContext
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] window Window.
		*/
		WindowContext(Context& context, EInfrastructure e, void* window = nullptr);

		/**
		* @brief Destructor Function.
		*/
		~WindowContext() override;

		/**
		* @brief Make Context Current.
		*/
		void MakeContextCurrent() override;

		/**
		* @brief Interface of SwapBuffers.
		*/
		void SwapBuffers() override;
		
	private:

		/**
		* @brief Create WindowContext.
		* 
		* @param[in] window Window.
		*/
		void Create(void* window = nullptr);
		
		/**
		* @brief Create Window.
		* 
		* @return Returns Window.
		*/
		void* CreateWindow();

	};

}

#endif