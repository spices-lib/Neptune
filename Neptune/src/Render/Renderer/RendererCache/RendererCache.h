/**
* @file RendererCache.h
* @brief The RendererCache Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include <any>

namespace Neptune {

	/**
	* @brief Caches of Renderer data.
	* This class treats all stored caches as garbage and actively cleans them up.
	*/
	class RendererCache
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		RendererCache() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~RendererCache()
		{
			NEPTUNE_PROFILE_ZONE;
			
			ClearCaches();
		}

		/**
		* @brief Push a garbage to caches.
		* @param[in] any anything.
		*/
		template<typename T>
		void PushToCaches(T&& any)
		{
			NEPTUNE_PROFILE_ZONE;

			std::unique_lock<std::mutex> lock(m_Mutex);
			
			m_Caches.push_back(any);
		}

		/**
		* @brief Clear all caches.
		*/
		void ClearCaches()
		{
			NEPTUNE_PROFILE_ZONE;

			std::unique_lock<std::mutex> lock(m_Mutex);
			
			m_Caches.clear();
		}

	private:

		/**
		* @brief Renderer caches data.
		*/
		std::vector<std::any> m_Caches;

		/**
		* @brief This caches mutex. 
		*/
		std::mutex m_Mutex;
	};
}