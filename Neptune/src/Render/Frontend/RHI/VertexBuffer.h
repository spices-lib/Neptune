/**
* @file VertexBuffer.h.
* @brief The VertexBuffer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {
	
	using RHIVertexBuffer = RHI<ERHI::VertexBuffer>;

	/**
	* @brief Specialization of RHIVertexBuffer::Impl
	*/
	template<>
	class RHIVertexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;
	};

	/**
	* @brief RHI of ERHI::VertexBuffer
	*/
	class VertexBuffer : public RHIVertexBuffer
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		VertexBuffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~VertexBuffer() override = default;

	};
}