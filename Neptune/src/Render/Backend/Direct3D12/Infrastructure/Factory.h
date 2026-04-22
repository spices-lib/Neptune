/**
* @file Factory.h.
* @brief The Factory Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/Factory.h"

namespace Neptune::Direct3D12 {

	using IFactory = IInfrastructure<class Factory, EInfrastructure::Factory>;

	/**
	* @brief Direct3D12::Factory Class.
	* This class defines the Direct3D12::Factory behaves.
	*/
	class Factory : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Factory(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Factory() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Factory::Handle& Handle() const { return m_Factory.GetHandle(); }

	private:

		/**
		* @brief Create Device.
		*/
		void Create();

	private:

		Unit::Factory m_Factory;           // @brief this Factory.
	};

}

#endif