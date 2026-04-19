/**
* @file PipelineState.h.
* @brief The PipelineState Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::PipelineState Class.
	* This class defines the Direct3D12::Unit::PipelineState behaves.
	*/
	class PipelineState : public Unit<D3D12PipelineState>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		PipelineState() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~PipelineState() override;

		/**
		* @brief Create PipelineState.
		*
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_PIPELINE_STATE_STREAM_DESC.
		*/
		void CreatePipelineState(D3D12Device device, const D3D12_PIPELINE_STATE_STREAM_DESC& desc);

	};
}

#endif