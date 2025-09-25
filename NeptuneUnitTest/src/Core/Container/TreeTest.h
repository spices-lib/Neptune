/**
* @file TreeTest.h.
* @brief The TreeTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <gmock/gmock.h>
#include <Core/Container/Tree.hpp>

namespace Neptune::Test {

	/**
	* @brief Unit Test for TreeTest
	*/
	class TreeTest : public testing::Test
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
		
		Tree<int> m_Tree;
	};
	
	/**
	* @brief Testing Tree Constructor.
	*/
	TEST_F(TreeTest, Constructor) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		{
			EXPECT_EQ(m_Tree.GetData(), 0);
		}
		
		{
			const Tree<float> tree;
			
			EXPECT_FLOAT_EQ(tree.GetData(), 0.0f);
		}

		{
			const Tree<void*> tree;
			
			EXPECT_EQ(tree.GetData(), nullptr);
		}

		{
			struct TestStruct
			{
				int a = 1;
				float b = 2.0f;
			};

			const Tree<TestStruct> tree;

			EXPECT_EQ(tree.GetData().a, 1);
			EXPECT_FLOAT_EQ(tree.GetData().b, 2.0f);
		}
	}

	/**
	* @brief Testing Tree AddChild.
	*/
	TEST_F(TreeTest, AddChild) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		auto child = &m_Tree;
		
		for (int i = 0; i < 1000; i++)
		{
			child = child->AddChild(i);

			EXPECT_EQ(child->GetData(), i);
		}
	}

	/**
	* @brief Testing Tree View.
	*/
	TEST_F(TreeTest, View) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		m_Tree.View([](const auto& data) {

			EXPECT_EQ(data, 0);
		});

		m_Tree.View([](auto& data) {

			data = 1;
		});

		m_Tree.View([](const auto& data) {
			
			EXPECT_EQ(data, 1);
		});
	}

	/**
	* @brief Testing Tree ViewDSF ViewWSF.
	*/
	TEST_F(TreeTest, ViewDSF_ViewWSF) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		const auto c0 = &m_Tree;
		
		// max depth = 3
		for (int i = 0; i < 10; i++)
		{
			const auto c1 = c0->AddChild(i);

			for (int j = 0; j < 10; j++)
			{
				const auto c2 = c1->AddChild(j);

				for (int k = 0; k < 10; k++)
				{
					const auto c3 = c2->AddChild(k);
				}
			}
		}

		{
			uint32_t count = 0;

			m_Tree.ViewDSF([&](const auto& data, uint32_t depth) {

				++count;
				return true;
			});

			EXPECT_EQ(count, 1 + 10 + 100 + 1000);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewWSF([&](const auto& data, uint32_t depth) {

				++count;
				return true;
			});

			EXPECT_EQ(count, 1 + 10 + 100 + 1000);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewDSF([&](const auto& data, uint32_t depth) {

				if (depth == 3)
				{
					return false;
				}

				++count;
				return true;
			});

			EXPECT_EQ(count, 1 + 1 + 1);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewWSF([&](const auto& data, uint32_t depth) {

				if (depth == 3)
				{
					return false;
				}

				++count;
				return true;
			});

			EXPECT_EQ(count, 1 + 10 + 100);
		}
	}
	
}