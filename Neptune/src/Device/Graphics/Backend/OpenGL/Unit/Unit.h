/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"
#include "Device/Graphics/Backend/Common/Unit/Unit.h"

namespace Neptune::OpenGL::Unit {

	using namespace Render::Common;

	template<typename T, auto E>
	requires IsUnit<Render::Common::Unit<T, E>>
	using Unit = Render::Common::Unit<T, E>;
}

#endif