/**
* @file CommonTest.h.
* @brief The CommonTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Render/Backend/Common/Unit/Unit.h>
#include <Render/Backend/Common/Infrastructure/Infrastructure.h>
#include <Core/Container/Tuple.h>

#include <gmock/gmock.h>

namespace Neptune::Render::Common::Test {

	namespace details {

		enum class EInfrastructure0 : uint8_t { Count };
		enum class EInfrastructure1 : uint8_t { One, Count };
		enum class EInfrastructure2 : uint8_t { One, Two, Count };
		enum class EInfrastructure3 : uint8_t { One, Two, Three, Count };
		enum class EInfrastructure4 : uint8_t { One, Two, Three, Four, Count };
		enum class EInfrastructure5 : uint8_t { One, Two, Three, Four, Five, Count };
		enum class EInfrastructure6 : uint8_t { One, Two, Three, Four, Five, Six, Count };
		enum class EInfrastructure7 : uint8_t { One, Two, Three, Four, Five, Six, Seven, Count };
		enum class EInfrastructure8 : uint8_t { One, Two, Three, Four, Five, Six, Seven, Eight, Count };
		enum class EInfrastructure9 : uint8_t { One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Count };

		using EnumTuple = std::tuple<
			EInfrastructure0,
			EInfrastructure1,
			EInfrastructure2,
			EInfrastructure3,
			EInfrastructure4,
			EInfrastructure5,
			EInfrastructure6,
			EInfrastructure7,
			EInfrastructure8,
			EInfrastructure9
		>;
	}

	/**
	* @brief Testing Unit Class.
	*/
	TEST(UnitTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		Unit<void*, 0>{};
		
		details::EnumTuple tuple;
		
		Container::IterTuple(tuple, []<typename EInfrastructure>(EInfrastructure& e) {
		
#define UNIT_DEFINE_WITH_ENUM(Id)                                                                         \
			if constexpr (requires{ { EInfrastructure::Id } -> std::convertible_to<EInfrastructure>; }) { \
				                                                                                          \
				const auto unit0 = Unit<size_t*, static_cast<uint8_t>(EInfrastructure::Id)>{};            \
				const auto unit1 = Unit<size_t , EInfrastructure::Id>{};                                  \
				                                                                                          \
				EXPECT_EQ(sizeof(decltype(unit0)), sizeof(decltype(unit0)::Handle) + sizeof(size_t));     \
				EXPECT_EQ(sizeof(decltype(unit1)), sizeof(decltype(unit1)::Handle) + sizeof(size_t));     \
			                                                                                              \
				EXPECT_LE(sizeof(decltype(unit0)::Handle), sizeof(size_t));                               \
				EXPECT_LE(sizeof(decltype(unit1)::Handle), sizeof(size_t));                               \
			}
			
			UNIT_DEFINE_WITH_ENUM(Count)
			UNIT_DEFINE_WITH_ENUM(One)
			UNIT_DEFINE_WITH_ENUM(Two)
			UNIT_DEFINE_WITH_ENUM(Three)
			UNIT_DEFINE_WITH_ENUM(Four)
			UNIT_DEFINE_WITH_ENUM(Five)
			UNIT_DEFINE_WITH_ENUM(Six)
			UNIT_DEFINE_WITH_ENUM(Seven)
			UNIT_DEFINE_WITH_ENUM(Eight)
			UNIT_DEFINE_WITH_ENUM(Nine)

#undef UNIT_DEFINE_WITH_ENUM

		});
	}
	
	/**
	* @brief Testing Context Class.
	*/
	TEST(ContextTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		details::EnumTuple tuple;
		
		Container::IterTuple(tuple, []<typename EInfrastructure>(EInfrastructure& e) {
			
			const auto context = Context<EInfrastructure>{};
			
			if constexpr (static_cast<uint8_t>(EInfrastructure::Count))
			{
				constexpr uint32_t size = context.m_Infrastructures.size();
				
				EXPECT_EQ(size, static_cast<uint8_t>(EInfrastructure::Count));

				// Context bytes equals to EInfrastructure::Count * sizeof(size_t)
				EXPECT_EQ(sizeof(decltype(context)), size * sizeof(SP<Infrastructure<EInfrastructure>>));
			}
			else
			{
				EXPECT_EQ(sizeof(decltype(context)), 1);
			}
		});
	}

	/**
	* @brief Testing Context Class.
	*/
	TEST(ContextAccessorTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		details::EnumTuple tuple;
		
		Container::IterTuple(tuple, []<typename EInfrastructure>(EInfrastructure & e) {

			auto context = Context<EInfrastructure>{};

			const auto contextAccessor = ContextAccessor<EInfrastructure>(context);

			// ContextAccessor bytes equals to Context bytes
			EXPECT_EQ(sizeof(decltype(contextAccessor)), sizeof(decltype(context)));

		});
	}
}