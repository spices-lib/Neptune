/**
* @file CommandAllocator.h.
* @brief The CommandAllocator Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/CommandAllocator.h"

namespace Neptune::Direct3D12 {

	using IGraphicCommandAllocator = IInfrastructure<class CommandAllocator, EInfrastructure::GraphicCommandAllocator>;
	using IComputeCommandAllocator = IInfrastructure<class CommandAllocator, EInfrastructure::ComputeCommandAllocator>;

	/**
	* @brief Direct3D12::CommandAllocator Class.
	* This class defines the Direct3D12::CommandAllocator behaves.
	*/
	class CommandAllocator : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		CommandAllocator(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~CommandAllocator() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::CommandAllocator::Handle& Handle() const { return m_CommandAllocator.GetHandle(); }

	private:

		/**
		* @brief Create CommandPool.
		*/
		void Create();

		/**
		* @brief Get CommandListType.
		*
		* @return Returns CommandListType.
		*/
		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

	private:

		Unit::CommandAllocator m_CommandAllocator; // @brief this CommandAllocator.

	};

}

#endif