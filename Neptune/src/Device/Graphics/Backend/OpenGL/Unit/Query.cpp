/**
* @file Query.cpp.
* @brief The Query Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Query.h"

namespace Neptune::OpenGL::Unit {

	Query::~Query()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteQueries(1, &m_Handle);
	}

	void Query::CreateQuery()
	{
		NEPTUNE_PROFILE_ZONE

		glGenQueries(1, &m_Handle);
	}
}

#endif