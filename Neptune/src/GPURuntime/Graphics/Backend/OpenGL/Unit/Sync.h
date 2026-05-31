/**
* @file Sampler.h.
* @brief The Sampler Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Sync Class.
	* This class defines the OpenGL::Unit::Sync behaves.
	*/
	class Sync : public Unit<GLsync, GL_SYNC_FENCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Sync() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Sync() override;

		/**
		* @brief Create Sync.
		*/
		void CreateSync();

		/**
		* @brief Sync client wait idle.
		* Like vkFence.
		* sync between CPU and GPU.
		*/
		void ClientWait() const;

		/**
		* @brief Sync wait.
		* Like pipeline barrier or vkCmdWaitEvents.
		* sync between GPU and GPU.
		*/
		void Wait() const;
	};
}

#endif