/**
* @file CommandList.h.
* @brief The CommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/GraphicsCommandList.h"

#include <vector>

namespace Neptune::Direct3D12 {

	using IGraphicCommandList     = IInfrastructure<class CommandList, EInfrastructure::GraphicCommandList>;
	using IComputeCommandList     = IInfrastructure<class CommandList, EInfrastructure::ComputeCommandList>;

	/**
	* @brief Direct3D12::CommandList Class.
	* This class defines the Direct3D12::CommandList behaves.
	*/
	class CommandList : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count CommandBuffer Counts.
		*/
		CommandList(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~CommandList() override = default;

		/**
		* @brief Get Unit Handle.
		* 
		* @param[in] index Handle index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::GraphicsCommandList::Handle& Handle(uint32_t index = 0) const { return m_CommandLists[index]->GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @param[in] index Handle index.
		*
		* @return Returns Unit Handle Interface.
		*/
		const SP<Unit::GraphicsCommandList> IHandle(uint32_t index = 0) const { return m_CommandLists[index]; }

		/**
		* @brief Begin CommandBuffer.
		*
		* @param[in] index Handle index.
		*/
		void Begin(uint32_t index = 0) const;

		/**
		* @brief End CommandBuffer.
		*
		* @param[in] index Handle index.
		*/
		void End(uint32_t index = 0) const;

	private:

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] count CommandBuffer Counts.
		*/
		void Create(uint32_t count);

		/**
		* @brief Get Unit CommandAllocator Handle which allocated this CommandList.
		*
		* @return Returns Unit CommandAllocator Handle which allocated this CommandList.
		*/
		const D3D12CommandAllocator& GetCommandAllocator() const;

		/**
		* @brief Get CommandListType.
		*
		* @return Returns CommandListType.
		*/
		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

	private:

		std::vector<SP<Unit::GraphicsCommandList>> m_CommandLists;  // @brief Container of this unit CommandList.

	};

}

#endif