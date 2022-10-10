//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include "../../TLT_Qn_1/RoomManager.h"

class RoomManagerTest : public ::testing::Test
{
protected:
	void SetUp() override {
		std::vector<std::string> rms = 
			{"1B", "1C", "1D",
			"2A", "2B", "2C", "2D", "2E",
			"3A", "3B", "3C", "3D", "3E",
			"4A", "4B", "4C", "4D", "4E"};

		for (auto& r : rms)
			rm_test.addRoomToList(r);
	}

	RoomManager rm_test;
};