/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Common/Unit/Unit.h"

namespace Neptune::Vulkan::Unit {

	using namespace Render::Common;
	
	template<typename T, auto E>
	requires IsUnit<Render::Common::Unit<T, E>>
	using Unit = Render::Common::Unit<T, E>;
}

#endif