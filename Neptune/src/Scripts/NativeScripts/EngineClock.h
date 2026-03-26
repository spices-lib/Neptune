#pragma once
#include "Core/Core.h"
#include "NativeScript.h"

namespace Neptune {

	namespace Data {
		struct Clock;
	}

	class EngineClock : public NativeScript
	{
	public:

		EngineClock(class Scene* scene);
		~EngineClock() override = default;

		void OnAttached() override;
		void OnTick() override;

	private:

		Scene* m_Scene = nullptr;
		Data::Clock* m_Clock = nullptr;

		SP<class Timer> m_Timer = nullptr;
	};
}