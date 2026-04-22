/**
* @file DebugUtilsObject.h.
* @brief The DebugUtilsObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Core.h"

namespace Neptune::Direct3D12 {

	using IDebugUtilsObject = IInfrastructure<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

	/**
	* @brief Direct3D12::DebugUtilsObject Class.
	* This class defines the Direct3D12::DebugUtilsObject behaves.
	*/
	class DebugUtilsObject : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		DebugUtilsObject(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~DebugUtilsObject() override = default;

		/**
		* @brief Begin CommandBuffer Label.
		*
		* @param[in] cmdList D3D12GraphicsCommandList.
		* @param[in] caption Label String.
		*/
		void BeginLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const;

		/**
		* @brief End CommandBuffer Label.
		* 
		* @param[in] cmdList D3D12GraphicsCommandList.
		*/
		void EndLabel(D3D12GraphicsCommandList cmdList) const;

		/**
		* @brief Insert CommandBuffer Label.
		*
		* @param[in] cmdList D3D12GraphicsCommandList.
		* @param[in] caption Label String.
		*/
		void InsertLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const;

		/**
		* @brief Set Unit Name.
		*
		* @tparam Unit Unit.
		* @param[in] caption Label String.
		*/
		template<typename Unit>
		void SetObjectName(const Unit& unit, const std::string& caption);

	};
	

#ifdef NEPTUNE_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 { GetContext().Get<IDebugUtilsObject>()->BeginLabel       (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDLABEL(...)                   { GetContext().Get<IDebugUtilsObject>()->EndLabel         (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTLABEL(...)                { GetContext().Get<IDebugUtilsObject>()->InsertLabel      (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTNAME(...)              { GetContext().Get<IDebugUtilsObject>()->SetObjectName    (__VA_ARGS__)	; }

#endif

#ifdef NEPTUNE_RELEASE

#define DEBUGUTILS_BEGINLABEL(...)      
#define DEBUGUTILS_ENDLABEL(...)         
#define DEBUGUTILS_INSERTLABEL(...)
#define DEBUGUTILS_SETOBJECTNAME(...)                

#endif

	template<typename Unit>
	inline void DebugUtilsObject::SetObjectName(const Unit& unit, const std::string& caption)
	{
		NEPTUNE_PROFILE_ZONE
		
		if constexpr (requires() {
			{ Unit::Handle::SetName() } -> std::convertible_to<void>;
		})
		{
			unit.GetHandle()->SetName(caption.c_str());
		}
	}
	
}

#endif