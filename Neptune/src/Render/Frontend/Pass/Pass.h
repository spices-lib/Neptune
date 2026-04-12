/**
* @file Pass.h.
* @brief The Pass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

	class Scene;
}

namespace Neptune::Render { 

	/**
	* @brief Pass Class.
	*/
	class Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Pass() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Pass() = default;

		/**
		* @brief Interface of Construct.
		*/
		virtual void OnConstruct() = 0;

		/**
		* @brief Interface of Render.
		*
		* @param[in] scene Scene.
		*/
		virtual void OnRender(Scene* scene) = 0;
	};
}