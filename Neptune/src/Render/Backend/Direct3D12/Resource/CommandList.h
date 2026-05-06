/**
* @file CommandList.h.
* @brief The CommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/CommandAllocator.h"
#include "Render/Backend/Direct3D12/Unit/GraphicsCommandList.h"

#include <vector>

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::CommandList Class.
	* This class defines the Direct3D12::CommandList behaves.
	*/
	class CommandList : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		*/
		CommandList(Context& context) : ContextAccessor(context)

		/**
		* @brief Destructor Function.
		*/
		~CommandList() override = default;

		/**
		* @brief Get Unit Handle.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::GraphicsCommandList::Handle& Handle() const { return m_CommandList.GetHandle(); }

		/**
		* @brief Create CommandList.
		* 
		* @param[in] device D3D12Device.
		* @param[in] type D3D12_COMMAND_LIST_TYPE.
		*/
		void CreateCommandList(D3D12Device device, D3D12_COMMAND_LIST_TYPE type);

		/**
		* @brief Begin CommandBuffer.
		*/
		void Begin();

		/**
		* @brief End CommandBuffer.
		*/
		void End();

	private:

		Unit::CommandAllocator    m_CommandAllocator; // @brief This unit CommandAllocator.
		Unit::GraphicsCommandList m_CommandList;      // @brief This unit CommandList.
		bool                      m_Open;             // @brief This unit CommandList State.

	};

}

#endif