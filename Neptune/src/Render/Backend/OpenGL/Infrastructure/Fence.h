/**
* @file Fence.h.
* @brief The Fence Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/OpenGL/Unit/Sync.h"

namespace Neptune::OpenGL {

	using IGraphicFence     = IInfrastructure<class Fence, EInfrastructure::GraphicFence>;

	/**
	* @brief OpenGL::Fence Class.
	* This class defines the OpenGL::Fence behaves.
	*/
	class Fence : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Fence count.
		*/
		Fence(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~Fence() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] index Fence index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::Sync::Handle& Handle(uint32_t index = 0) const { return m_Fences[index]->GetHandle(); }

		/**
		* @brief Fence wait idle.
		* 
		* @param[in] index Fence index.
		*/
		void Wait(uint32_t index);

		/**
		* @brief Fence wait barrier.
		*
		* @param[in] index Fence index.
		*/
		void Barrier(uint32_t index);

		/**
		* @brief All Fence wait idle.
		*/
		void WaitAll();

	private:

		/**
		* @brief Create Fence.
		* 
		* @param[in] count Fence count.
		*/
		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Sync>> m_Fences; // @brief Container of this Fence.

	};
	
}

#endif