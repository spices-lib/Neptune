#pragma once
#include "Core/Core.h"
#include "ViewBase.h"
#include "Slate/Frontend/ViewModel/Texture.h"
#include "Core/Event/SlateEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/EngineEvent.h"

namespace Neptune::View {

	class Texture : public ViewBase
	{
	public:

		Texture() : ViewBase() {}

		~Texture() override = default;

		

	private:

		void ResizeQuery();

	private:

		ViewModel::Texture m_ViewModel;
	};

}