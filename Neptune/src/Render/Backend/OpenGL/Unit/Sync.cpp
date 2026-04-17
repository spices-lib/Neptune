/**
* @file Sync.cpp.
* @brief The Sync Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Sync.h"

namespace Neptune::OpenGL::Unit {

	Sync::~Sync()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteSync(m_Handle);
	}

	void Sync::CreateSync()
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	void Sync::ClientWait() const
	{
		NEPTUNE_PROFILE_ZONE

		GLenum result = glClientWaitSync(m_Handle, GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000);  // ns

		if (result != GL_CONDITION_SATISFIED || result != GL_ALREADY_SIGNALED) 
		{
			NEPTUNE_CORE_ERROR("glClientWaitSync Failed.")
		}
	}

	void Sync::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		glWaitSync(m_Handle, 0, GL_TIMEOUT_IGNORED);
	}
	 
}

#endif