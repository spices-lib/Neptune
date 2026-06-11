/**
* @file DebugUtilsObject.h.
* @brief The DebugUtilsObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/UserDefinedAnnotation.h"
#include "Core/Library/StringLibrary.h"

namespace Neptune::Direct3D11 {

	using IDebugUtilsObject = IInfrastructure<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

	/**
	* @brief Direct3D11::DebugUtilsObject Class.
	* This class defines the Direct3D11::DebugUtilsObject behaves.
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
		* @brief Create DebugUtilsObject.
		*/
		void Create();

		/**
		* @brief Begin CommandBuffer Label.
		*
		* @param[in] caption Label String.
		*/
		void BeginLabel(const std::string& caption) const;

		/**
		* @brief End CommandBuffer Label.
		* 
		*/
		void EndLabel() const;

		/**
		* @brief Insert CommandBuffer Label.
		*
		* @param[in] caption Label String.
		*/
		void InsertLabel(const std::string& caption) const;
		
		/**
		* @brief Set Unit Name.
		*
		* @tparam Unit Unit.
		* @param[in] caption Label String.
		*/
		template<typename Unit>
		void SetObjectName(const Unit& unit, const std::string& caption);

	private:

		Unit::UserDefinedAnnotation m_UserDefinedAnnotation;  // @brief this UserDefinedAnnotation.

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

		using Handle = std::remove_pointer_t<typename Unit::Handle>;

		if constexpr (requires(Handle& h, LPCWSTR name) {
			{ h.SetName(name) } -> std::convertible_to<HRESULT>;
		})
		{
			DIRECT3D11_CHECK(unit.GetHandle()->SetName(StringLibrary::CharToWChar(caption.c_str()).c_str()))
		}
	}
	
}

#endif