/**
* @file CommandList.h.
* @brief The CommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/DeviceContext.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/CommandList.h"

namespace Neptune::Direct3D11::Resource {

	/**
	* @brief Direct3D11::CommandList Class.
	* This class defines the Direct3D11::CommandList behaves.
	*/
	class CommandList : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		*/
		explicit CommandList(Context& context) : ContextAccessor(context) { CreateDeviceContext(); }

		/**
		* @brief Destructor Function.
		*/
		~CommandList() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::CommandList::Handle& Handle() const { return m_CommandList->GetHandle(); }

		/**
		* @brief Get DeviceContext Unit Handle.
		* 
		* @return Returns DeviceContext Unit Handle.
		*/
		const Unit::DeviceContext::Handle& DeviceContext() const { return m_Context.GetHandle(); }

		/**
		* @brief Finish DeviceContext.
		*/
		void Finish();

	private:

		/**
		* @brief Create DeviceContext.
		*/
		void CreateDeviceContext();

	private:

		Unit::DeviceContext   m_Context;       // @brief This unit DeviceContext.
		UP<Unit::CommandList> m_CommandList;   // @brief This unit CommandList.

	};

}

#endif