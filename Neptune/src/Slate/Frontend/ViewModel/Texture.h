#pragma once
#include "Core/Core.h"
#include "ViewModelBase.h"

namespace Neptune::ViewModel {

	class Texture : public ViewModelBase
	{
	public:

		Texture() = default;
		virtual ~Texture() = default;

		void OnTick() override {}
		void OnEvent(Event& event) override {}

	private:


	};

}