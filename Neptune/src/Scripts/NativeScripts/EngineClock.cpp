#include "EngineClock.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"
#include "Render/Frontend/Utils.h"
#include "Core/Timer/Timer.h"

namespace Neptune {

	EngineClock::EngineClock(Scene* scene)
		: m_Scene(scene)
	{}

	void EngineClock::OnAttached()
	{
		auto& comp = m_Scene->AddComponent<ClockComponent>(m_Scene->GetRoot());
		m_Clock = &comp.GetClock();
	}

	void EngineClock::OnTick()
	{
		if (!m_Timer)
		{
			m_Timer = CreateSP<Timer>();

			// First frame skip count.
			return;
		}

		m_Timer->Flush();

		m_Clock->m_FrameTime  = m_Timer->SegmentTime();
		m_Clock->m_EngineTime = m_Timer->DurationTime();
		m_Clock->m_FrameIndex = (m_Clock->m_FrameIndex + 1) % MaxFrameInFlight;
	}
}