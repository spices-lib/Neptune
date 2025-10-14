/**
* @file SpinLockTest.h.
* @brief The SpinLockTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/SpinLock.hpp>
#include <gmock/gmock.h>

namespace Neptune::Test {

	/**
	* @brief Unit Test for SpinLock
	*/
	class SpinLockTest : public testing::Test
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
	* @brief Testing SpinLockTest Class.
	*/
	TEST(SpinLockTest, All) {

		NEPTUNE_TEST_PROFILE_FUNCTION

	}
}