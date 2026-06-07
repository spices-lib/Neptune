/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Core.h"
#include "Device/Graphics/Backend/Common/Unit/Unit.h"

#include <entt.hpp>

namespace Neptune::Direct3D11::Unit {

	using namespace Render::Common;

	template<typename T>
	requires IsUnit<Render::Common::Unit<T, entt::type_hash<T>::value()>>
	using Unit = Render::Common::Unit<T, entt::type_hash<T>::value()>;
}