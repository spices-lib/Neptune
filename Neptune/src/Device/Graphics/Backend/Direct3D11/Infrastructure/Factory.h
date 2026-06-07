/**
* @file Factory.h.
* @brief The Factory Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/Factory.h"

namespace Neptune::Direct3D11 {

	using IFactory = IInfrastructure<class Factory, EInfrastructure::Factory>;

	/**
	* @brief Direct3D11::Factory Class.
	* This class defines the Direct3D11::Factory behaves.
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

		Unit::Factory m_Factory; // @brief this Factory.
	};

}

#endif