/**
* @file Sync.cpp.
* @brief The Sync Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Sync.h"

namespace Neptune::OpenGL::Unit {

	namespace {
	
		void HandleResult(GLenum result)
		{
			switch (result) {
				case GL_ALREADY_SIGNALED:   break;          // Already done.
				case GL_CONDITION_SATISFIED: break;         // Wait for done.
				case GL_TIMEOUT_EXPIRED:                    // Timeout
				{
					NEPTUNE_CORE_ERROR("glClientWaitSync Timeout.")
					break;
				}
				case GL_WAIT_FAILED:                        // Failed
				{
					NEPTUNE_CORE_ERROR("glClientWaitSync Failed.")

					OPENGL_CHECK

					break;
				}
				default:
				{
					NEPTUNE_CORE_WARN("glClientWaitSync Unkonwn Warnin.")

					OPENGL_CHECK

					break;
				}
			}
		}
		
	}

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

		HandleResult(glClientWaitSync(m_Handle, GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000));  // ns
	}

	void Sync::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		glWaitSync(m_Handle, 0, GL_TIMEOUT_IGNORED);
	}
	 
}

#endif