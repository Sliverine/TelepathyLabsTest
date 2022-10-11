//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include "../../TLT_Qn_2/IntervalList.h"

class IntervalListTest : public ::testing::Test
{
protected:
	void SetUp() override {
		for (int x = 1; x < 10; x+=2) {
			for (int y = 1; y<= 10; ++y) {
				it_test.insert(std::make_pair(x, y));
			}
		}

		/*srand(time(NULL));
		int count = 0, abs_count = 500;
		while (count < NUM_PTS_GENERATED && abs_count > 0) {
			abs_count--;

			int x = rand() % 100;
			int y = rand() % 100;

			if (rand() % 2)
				x *= -1;
			if (rand() % 2)
				y *= -1;

			auto itv = std::make_pair(x, y);
			if (!it_test.hasExactInterval(itv)) {
				
				count++;
			}
		}*/
	}

	IntervalList it_test;
};
