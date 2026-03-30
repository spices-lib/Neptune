/**
* @file RHI.h.
* @brief The RHI Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <functional>
#include <any>

namespace Neptune::RHI {
	
	/**
	* @brief Enum of RHI.
	*/
	enum class ERHI : uint8_t
	{
		RenderPass = 0,
		DescriptorList,
		Pipeline,
		Shader,
		RenderTarget,
		VertexBuffer,
		IndexBuffer,
		CmdList,
		CmdList2,
		Decoder,
		OpticalFlow,

		Count
	};

	/**
	* @brief Delegate of RHI.
	*/
	struct RHIDelegate
	{
		/**
		* @brief RHI Creator Functor.
		* 
		* @param[in] e ERHI.
		* @param[in] payload payload of rhi.
		*/
		using Creator = std::function<std::any(ERHI e, void* payload)>;

		/**
		* @brief Set Creator Functor.
		*
		* @param[in] fn Creator.
		*/
		static void SetCreator(const Creator& fn);

		/**
		* @brief Get Creator Functor.
		*
		* @return Returns Creator Functor.
		*/
		static const Creator& GetCreator();
	};

	/**
	* @brief Template of RHI Class.
	*/
	template<ERHI E>
	class RHI
	{
	public:

		/**
		* @brief Template of RHI Implement Class.
		*/
		class Impl
		{	
		public:

			/**
			* @brief Constructor Function.
			*/
			Impl() = default;

			/**
			* @brief Destructor Function.
			*/
			virtual ~Impl() = default;
		};

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] payload RHI Construct payload.
		*/
		explicit RHI(void* payload = nullptr)
		{
			NEPTUNE_PROFILE_ZONE

			if (auto p = std::any_cast<SP<Impl>>(std::invoke(RHIDelegate::GetCreator(), E, payload)))
			{
				m_Impl = p;
			}
			else
			{
				NEPTUNE_CORE_ERROR("RHI Create With Wrong ERHI")
			}
		}

		/**
		* @brief Destructor Function.
		*/
		virtual ~RHI() = default;

		/**
		* @brief Get RHI Implement.
		* 
		* @return Returns RHI Implement.
		*/
		template<typename T>
		WP<T> GetRHIImpl()
		{
			NEPTUNE_PROFILE_ZONE

			return std::dynamic_pointer_cast<T>(m_Impl);
		}

	protected:

		SP<Impl> m_Impl = nullptr;     // @brief RHI Implement.
	};
}