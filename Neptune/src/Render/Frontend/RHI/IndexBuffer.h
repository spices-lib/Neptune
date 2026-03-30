/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {
	
	using RHIIndexBuffer = RHI<ERHI::IndexBuffer>;

	/**
	* @brief Specialization of RHIIndexBuffer::Impl
	*/
	template<>
	class RHIIndexBuffer::Impl
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
	* @brief RHI of ERHI::IndexBuffer
	*/
	class IndexBuffer : public RHIIndexBuffer
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		IndexBuffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~IndexBuffer() override = default;

	};
}