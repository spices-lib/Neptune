/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Core.h"
#include "Render/Backend/Common/Unit/Unit.h"

#include <entt.hpp>

namespace Neptune::Direct3D12::Unit {

	using namespace Render::Common;

	template<typename T>
	requires IsUnit<Render::Common::Unit<T, entt::type_hash<T>::value()>>
	using Unit = Render::Common::Unit<T, entt::type_hash<T>::value()>;
}