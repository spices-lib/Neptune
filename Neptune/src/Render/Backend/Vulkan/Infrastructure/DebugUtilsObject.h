/**
* @file DebugUtilsObject.h.
* @brief The DebugUtilsObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Functions.h"
#include "Render/Backend/Vulkan/Unit/Device.h"

#include <glm/glm.hpp>
#include <vector>

namespace Neptune::Vulkan {

	using IDebugUtilsObject = InfrastructureClass<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

	/**
	* @brief Vulkan::DebugUtilsObject Class.
	* This class defines the Vulkan::DebugUtilsObject behaves.
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
		* @param[in] cmdBuffer VkCommandBuffer.
		* @param[in] caption Label String.
		* @param[in] color Label Color.
		*/
		void BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		/**
		* @brief End CommandBuffer Label.
		*
		* @param[in] cmdBuffer VkCommandBuffer.
		*/
		void EndLabel(VkCommandBuffer cmdBuffer) const;

		/**
		* @brief Insert CommandBuffer Label.
		*
		* @param[in] cmdBuffer VkCommandBuffer.
		* @param[in] caption Label String.
		* @param[in] color Label Color.
		*/
		void InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		/**
		* @brief Begin Queue Label.
		*
		* @param[in] queue VkQueue.
		* @param[in] caption Label String.
		* @param[in] color Label Color.
		*/
		void BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		/**
		* @brief End Queue Label.
		*
		* @param[in] queue VkQueue.
		*/
		void EndQueueLabel(VkQueue queue) const;

		/**
		* @brief Insert Queue Label.
		*
		* @param[in] queue VkQueue.
		* @param[in] caption Label String.
		* @param[in] color Label Color.
		*/
		void InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		/**
		* @brief Set Unit Name.
		*
		* @tparam Unit Unit.
		* @param[in] caption Label String.
		*/
		template<typename Unit>
		void SetObjectName(const Unit& unit, const std::string& caption);
		
		/**
		* @brief Set Unit Tag.
		*
		* @tparam Unit Unit.
		* @param[in] captions Label Strings.
		*/
		template<typename Unit>
		void SetObjectTag(const Unit& unit, const std::vector<char*>& captions) const;

	private:

		VkDevice m_Device = VK_NULL_HANDLE; // @brief This VkDevice.
	};
	
#ifdef NEPTUNE_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 { GetContext().Get<IDebugUtilsObject>()->BeginLabel       (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDLABEL(...)                   { GetContext().Get<IDebugUtilsObject>()->EndLabel         (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTLABEL(...)                { GetContext().Get<IDebugUtilsObject>()->InsertLabel      (__VA_ARGS__)	; }
#define DEBUGUTILS_BEGINQUEUELABEL(...)            { GetContext().Get<IDebugUtilsObject>()->BeginQueueLabel  (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDQUEUELABEL(...)              { GetContext().Get<IDebugUtilsObject>()->EndQueueLabel    (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTQUEUELABEL(...)           { GetContext().Get<IDebugUtilsObject>()->InsertQueueLabel (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTNAME(...)              { GetContext().Get<IDebugUtilsObject>()->SetObjectName    (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTTAG(...)               { GetContext().Get<IDebugUtilsObject>()->SetObjectTag     (__VA_ARGS__)	; }

#endif

#ifdef NEPTUNE_RELEASE

#define DEBUGUTILS_BEGINLABEL(...)      
#define DEBUGUTILS_ENDLABEL(...)        
#define DEBUGUTILS_INSERTLABEL(...)     
#define DEBUGUTILS_BEGINQUEUELABEL(...) 
#define DEBUGUTILS_ENDQUEUELABEL(...)   
#define DEBUGUTILS_INSERTQUEUELABEL(...)
#define DEBUGUTILS_SETOBJECTNAME(...)   
#define DEBUGUTILS_SETOBJECTTAG(...)                 

#endif

	template<typename Unit>
	inline void DebugUtilsObject::SetObjectName(const Unit& unit, const std::string& caption)
	{
		NEPTUNE_PROFILE_ZONE

		if (!unit.GetHandle()) return;

		VkDebugUtilsObjectNameInfoEXT       name_info{};
		name_info.sType                   = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		name_info.objectType              = Unit::GetEUnit();
		name_info.objectHandle            = reinterpret_cast<uint64_t>(unit.GetHandle());
		name_info.pObjectName             = caption.c_str();

		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectNameEXT(m_Device, &name_info))
	}

	template<>
	inline void DebugUtilsObject::SetObjectName<Unit::Device>(const Unit::Device& unit, const std::string& caption)
	{
		NEPTUNE_PROFILE_ZONE

		assert(unit.GetHandle());

		m_Device = unit.GetHandle();
		
		VkDebugUtilsObjectNameInfoEXT       name_info{};
		name_info.sType                   = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		name_info.objectType              = Unit::Device::GetEUnit();
		name_info.objectHandle            = reinterpret_cast<uint64_t>(unit.GetHandle());
		name_info.pObjectName             = caption.c_str();

		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectNameEXT(unit.GetHandle(), &name_info))
	}
	
	template <typename Unit>
	inline void DebugUtilsObject::SetObjectTag(const Unit& unit, const std::vector<char*>& captions) const
	{
		NEPTUNE_PROFILE_ZONE

		if (!unit.GetHandle()) return;

		VkDebugUtilsObjectTagInfoEXT        tag_info{};
		tag_info.sType                    = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
		tag_info.objectType               = Unit::GetEUnit();
		tag_info.objectHandle             = reinterpret_cast<uint64_t>(unit.GetHandle());
		tag_info.tagName                  = 0;
		tag_info.tagSize                  = captions.size();
		tag_info.pTag                     = captions.data();
		
		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectTagEXT(m_Device, &tag_info))
	}
}

#endif