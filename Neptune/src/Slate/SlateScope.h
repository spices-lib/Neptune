#pragma once
#include "Core/Core.h"

namespace Neptune::Slate {

	class SlateScope
	{
	public:

		static void BeginScope();

		static void EndScope();
	};
}