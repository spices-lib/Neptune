/**
* @file CommandList.h.
* @brief The CommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Resource/CommandList.h"

#include <vector>

namespace Neptune::Direct3D11 {

	using IGraphicCommandList     = IInfrastructure<class CommandList, EInfrastructure::GraphicCommandList>;
	using IComputeCommandList     = IInfrastructure<class CommandList, EInfrastructure::ComputeCommandList>;

	/**
	* @brief Direct3D11::CommandList Class.
	* This class defines the Direct3D11::CommandList behaves.
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
		const Unit::CommandList::Handle& Handle(uint32_t index = 0) const { return m_CommandLists[index]->Handle(); }

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

	private:

		std::vector<SP<Resource::CommandList>> m_CommandLists; // @brief Container of this resource CommandList.

	};

}

#endif