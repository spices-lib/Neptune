/**
* @file DebugUtilsObject.h.
* @brief The DebugUtilsObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/OpenGL/Unit/Sync.h"

namespace Neptune::OpenGL {

	using IDebugUtilsObject = InfrastructureClass<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

	/**
	* @brief OpenGL::DebugUtilsObject Class.
	* This class defines the OpenGL::DebugUtilsObject behaves.
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
		* @param[in] id Label Source id.
		* @param[in] caption Label String.
		*/
		void BeginLabel(GLuint id, const std::string& caption) const;

		/**
		* @brief End CommandBuffer Label.
		*/
		void EndLabel() const;

		/**
		* @brief Set Unit Name.
		*
		* @tparam Unit Unit.
		* @param[in] caption Label String.
		*/
		template<typename Unit>
		void SetObjectName(const Unit& unit, const std::string& caption);

	private:

		/**
		* @brief Set OpenGL Debug Context.
		*/
		void SetDebugContext() const;

	};
	

#ifdef NEPTUNE_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 { GetContext().Get<IDebugUtilsObject>()->BeginLabel       (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDLABEL(...)                   { GetContext().Get<IDebugUtilsObject>()->EndLabel         (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTNAME(...)              { GetContext().Get<IDebugUtilsObject>()->SetObjectName    (__VA_ARGS__)	; }

#endif

#ifdef NEPTUNE_RELEASE

#define DEBUGUTILS_BEGINLABEL(...)      
#define DEBUGUTILS_ENDLABEL(...)         
#define DEBUGUTILS_SETOBJECTNAME(...)                

#endif

	template<typename Unit>
	inline void DebugUtilsObject::SetObjectName(const Unit& unit, const std::string& caption)
	{
		NEPTUNE_PROFILE_ZONE

		glObjectLabel(Unit::GetEUnit(), unit.GetHandle(), caption.size(), caption.c_str());
	}
	
	template<>
	inline void DebugUtilsObject::SetObjectName<Unit::Sync>(const Unit::Sync& unit, const std::string& caption)
	{
		NEPTUNE_PROFILE_ZONE

		glObjectPtrLabel(unit.GetHandle(), caption.size(), caption.c_str());
	}
}

#endif