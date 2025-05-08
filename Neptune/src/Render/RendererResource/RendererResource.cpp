/**
* @file RendererResource.cpp.
* @brief The RendererResource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RendererResource.h"

namespace Neptune {

	RendererResource::RendererResource(const RendererResourceCreateInfo& info)
		: m_Info(info)
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Set local variable.
		*/
		m_IsResizeable = info.isResizeable;


	}

	void RendererResource::OnResized(const uint32_t width, const uint32_t height)
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Go on if can resize,
		*/
		if (!m_IsResizeable) return;

		/**
		* @brief Update info's width.
		*/
		m_Info.width = width;

		/**
		* @brief Update info's height.
		*/
		m_Info.height = height;


	}
}