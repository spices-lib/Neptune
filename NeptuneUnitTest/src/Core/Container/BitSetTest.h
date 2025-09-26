/**
* @file BitSetTest.h.
* @brief The BitSetTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/BitSet.hpp>
#include <gmock/gmock.h>

namespace Neptune::Test {

	/**
	* @brief Unit Test for BitSet
	*/
	class BitSetTest : public testing::Test
	{
	protected:

		/**
		* @brief The interface is inherited from testing::Test.
		* Registry on Initialize.
		*/
		void SetUp() override {}

		/**
		* @brief Testing class TearDown function.
		*/
		void TearDown() override {}

	protected:

		//BitSet<int> m_BitSet;
	};

	/**
	* @brief Testing BitSetTest Class.
	*/
	TEST(BitSetTest, All) {

		NEPTUNE_TEST_PROFILE_FUNCTION

	}
}