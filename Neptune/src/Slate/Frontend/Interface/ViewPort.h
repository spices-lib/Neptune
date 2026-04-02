#pragma once
#include "Core/Core.h"
#include "Slate.h"
#include "Core/Event/SlateEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/EngineEvent.h"

namespace Neptune::Slate {

	class ViewPort : public Slate
	{
	public:

		ViewPort(const std::string& slateName)
			: Slate(slateName)
		{}

		~ViewPort() override = default;

		void OnTick() override;

	private:

		void ResizeQuery();

	private:

		ImTextureID m_TextureID{};
	};

}