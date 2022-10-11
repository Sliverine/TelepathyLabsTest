#include "pch.h"


TEST_F(IntervalListTest, InsertTest) {
	EXPECT_TRUE(it_test.insert(std::make_pair(2, 1)));
	EXPECT_FALSE(it_test.insert(std::make_pair(1, 1)));
}

TEST_F(IntervalListTest, SearchTest) {
	// search closest
	std::pair<int, int> searchKey = { 2, 1 };
	EXPECT_EQ(it_test.search(searchKey), std::make_tuple(true, 1, 1));
	// search equals
	searchKey = { 1, 9 };
	EXPECT_EQ(it_test.search(searchKey), std::make_tuple(true, 1, 9));
	// search out-of-range value
	searchKey = { 0, 5 };
	EXPECT_EQ(it_test.search(searchKey), std::make_tuple(false, 1, 5));
}

TEST_F(IntervalListTest, PrintTest) {
	std::vector<std::pair<int, int>> expected = {
		{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10},
		{3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, {3,7}, {3,8}, {3,9}, {3,10},
		{5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}, {5,8}, {5,9}, {5,10},
		{7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}, {7,8}, {7,9}, {7,10},
		{9,1}, {9,2}, {9,3}, {9,4}, {9,5}, {9,6}, {9,7}, {9,8}, {9,9}, {9,10}
	};

	EXPECT_EQ(it_test.printAll(), expected);
}