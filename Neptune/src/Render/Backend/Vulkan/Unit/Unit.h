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

	using namespace Common;
	
	template<typename T, auto E>
	using Unit = Common::Unit<T, E>;
}

#endif