/**
* @file Fence.h.
* @brief The Fence Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {

	using IGraphicFence     = IInfrastructure<class Fence, EInfrastructure::GraphicFence>;
	using IComputeFence     = IInfrastructure<class Fence, EInfrastructure::ComputeFence>;

	/**
	* @brief Direct3D12::Fence Class.
	* This class defines the Direct3D12::Fence behaves.
	*/
	class Fence : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Fence count.
		*/
		Fence(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~Fence() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] index Fence index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::Fence::Handle& Handle(uint32_t index = 0) const { return m_Fences[index]->GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @param[in] index Fence index.
		* 
		* @return Returns Unit Handle Interface.
		*/
		const SP<Unit::Fence>& IHandle(uint32_t index = 0) const { return m_Fences[index]; }
		
		/**
		* @brief Fence wait idle.
		* 
		* @param[in] index Fence index.
		*/
		void Wait(uint32_t index) const;

		/**
		* @brief All Fence wait idle.
		*/
		void WaitAll() const;

	private:

		/**
		* @brief Create Fence.
		* 
		* @param[in] count Fence count.
		*/
		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Fence>> m_Fences; // @brief Container of this Fence.

	};
	
}

#endif