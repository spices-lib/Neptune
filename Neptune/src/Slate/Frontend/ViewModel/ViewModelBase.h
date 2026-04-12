#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune::ViewModel {

	class ViewModelBase
	{
	public:

		ViewModelBase() = default;

		virtual ~ViewModelBase() = default;

        /**
        * @brief This interface is called on Slate Update.
        */
        virtual void OnTick() = 0;

        /**
        * @brief This interface is called on global event function pointer execute.
        *
        * @param[in] event Event.
        */
        virtual void OnEvent(Event& event) = 0;

	private:


	};

}