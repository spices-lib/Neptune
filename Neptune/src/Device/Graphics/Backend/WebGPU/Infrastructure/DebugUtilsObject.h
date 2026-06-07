/**
* @file DebugUtilsObject.h.
* @brief The DebugUtilsObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"

namespace Neptune::WebGPU {

    using IDebugUtilsObject = IInfrastructure<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

    /**
    * @brief WebGPU::DebugUtilsObject Class.
    * This class defines the WebGPU::DebugUtilsObject behaves.
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
		DebugUtilsObject(Context& context, EInfrastructure e) : Infrastructure(context, e) {}

		/**
		* @brief Destructor Function.
		*/
		~DebugUtilsObject() override = default;

    	/**
		* @brief Begin Label.
		* 
		* @param[in] caption Label String.
		*/
    	void BeginLabel(const std::string& caption) const;

    	/**
		* @brief End Label.
		*/
    	void EndLabel() const;

    	/**
		* @brief Insert Label.
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
        
    };

#ifdef NEPTUNE_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 
#define DEBUGUTILS_ENDLABEL(...)                   
#define DEBUGUTILS_INSERTLABEL(...)               
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

		if constexpr (requires(Unit& u, const std::string& name) {
			{ u.SetName(name) } -> std::convertible_to<void>;
		})
		{
			unit.SetName(caption);
		}
	}

}

#endif