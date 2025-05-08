/**
* @file RendererResourcePool.cpp.
* @brief The RendererResourcePool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RendererResourcePool.h"

namespace Neptune {

	void RendererResourcePool::OnSlateResize(uint32_t width, uint32_t height) const
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Call all Resource's OnResized().
		*/
		for (auto& pair : m_RendererResource)
		{
			pair.second->OnResized(width, height);
		}
	}


}