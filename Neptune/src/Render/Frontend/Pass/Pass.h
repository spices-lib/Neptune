#pragma once
#include "Core/Core.h"

namespace Neptune {

	class Scene;
}

namespace Neptune::Render { 

	class Pass
	{
	public:

		Pass() = default;
		virtual ~Pass() = default;

		virtual void OnConstruct() = 0;

		virtual void OnRender(Scene* scene) = 0;
	};
}