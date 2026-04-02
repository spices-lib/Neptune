/**
* @file SlateFrontend.h.
* @brief The SlateFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

	class SlateFrontend : public NonCopyable
	{
    public:

        /**
        * @brief Create Slate Frontend.
        *
        * @return Returns Slate Frontend pointer.
        */
        static SP<SlateFrontend> Create();

	public:

        /**
        * @brief Constructor Function.
        */
		SlateFrontend() = default;

        /**
        * @brief Destructor Function.
        */
		~SlateFrontend() = default;

        /**
        * @brief Interface of Initialize.
        */
		virtual void OnInitialize() = 0;

        /**
        * @brief Interface of ShutDown.
        */
		virtual void OnShutDown() = 0;

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() = 0;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() = 0;

	private:


	};

}