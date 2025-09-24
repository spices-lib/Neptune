/**
* @file TreeTest.h.
* @brief The TreeTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/Tree.hpp>
#include <gmock/gmock.h>

namespace Neptune::Test {

	/**
	* @brief Testing Tree Class.
	*/
	TEST(Tree, All) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		Tree<float> tree(0.0f);

		tree.AddChild(1.0f)->AddChild(2.0f)->AddChild(3.0f)->AddChild(4.0f);

		EXPECT_EQ(tree.GetData(), 0.0f);

		auto& a = tree.GetChild();
		EXPECT_EQ(a.size(), 1);
		EXPECT_EQ(a[0]->GetData(), 1.0f);

		auto& b = a[0]->GetChild();
		EXPECT_EQ(b.size(), 1);
		EXPECT_EQ(b[0]->GetData(), 2.0f);

		auto& c = b[0]->GetChild();
		EXPECT_EQ(c.size(), 1);
		EXPECT_EQ(c[0]->GetData(), 3.0f);

		auto& d = c[0]->GetChild();
		EXPECT_EQ(d.size(), 1);
		EXPECT_EQ(d[0]->GetData(), 4.0f);
	}
}