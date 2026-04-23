/**
* @file CommonTest.h.
* @brief The CommonTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Render/Backend/Common/Unit/Unit.h>
#include <Render/Backend/Common/Infrastructure/Infrastructure.h>

#include <gmock/gmock.h>

namespace Neptune::Render::Common::Test {

	enum class EInfrastructure : uint8_t
	{
		One = 0,

		Count
	};

	/**
	* @brief Testing Unit Class.
	*/
	TEST(UnitTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		Unit<void*, 0>{};
		Unit<uint32_t, static_cast<uint8_t>(EInfrastructure::One)>{};
		Unit<int, EInfrastructure::One>{};
		Unit<size_t, EInfrastructure::One>{};
	}
	
	/**
	* @brief Testing Context Class.
	*/
	TEST(ContextTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		const auto context = Context<EInfrastructure>{};
		
		constexpr uint32_t size = context.m_Infrastructures.size();
		
		EXPECT_EQ(size, static_cast<uint8_t>(EInfrastructure::Count));
	}
}