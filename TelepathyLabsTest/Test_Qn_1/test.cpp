#include "pch.h"


TEST_F(RoomManagerTest, HasRoom) {
	EXPECT_TRUE(rm_test.hasRoom("2b"));
	EXPECT_TRUE(rm_test.hasRoom("3B"));
	EXPECT_FALSE(rm_test.hasRoom("1A"));
}

TEST_F(RoomManagerTest, AddRoom) {
	EXPECT_TRUE(rm_test.addRoomToList("1a"));
	EXPECT_FALSE(rm_test.addRoomToList("1A"));
	EXPECT_TRUE(rm_test.hasRoom("1A"));

	EXPECT_TRUE(rm_test.addRoomToList(1, 'e'));
	EXPECT_FALSE(rm_test.addRoomToList("1E"));
	EXPECT_TRUE(rm_test.hasRoom("1E"));
}

TEST_F(RoomManagerTest, RequestAndAssignRoom) {
	RoomManager rm_temp;
	EXPECT_EQ(rm_temp.requestAndAssignRoom(), "");

	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1A");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1B");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1C");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1D");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1E");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "2A");
}

TEST_F(RoomManagerTest, CheckoutRoom) {
	EXPECT_TRUE(rm_test.roomCheckout("1A"));
	EXPECT_TRUE(rm_test.roomCheckout("1B"));
	EXPECT_TRUE(rm_test.roomCheckout("1d"));
	EXPECT_TRUE(rm_test.roomCheckout("1e"));
	EXPECT_FALSE(rm_test.roomCheckout("1A"));
	EXPECT_FALSE(rm_test.roomCheckout("1B"));
	EXPECT_FALSE(rm_test.roomCheckout("1D"));
	EXPECT_FALSE(rm_test.roomCheckout("1e"));
	EXPECT_FALSE(rm_test.roomCheckout("3C"));
}

TEST_F(RoomManagerTest, CleanRoom) {
	EXPECT_TRUE(rm_test.roomCleaned("1b"));
	EXPECT_FALSE(rm_test.roomCleaned("1B"));
	EXPECT_FALSE(rm_test.roomCleaned("4E"));
}

TEST_F(RoomManagerTest, RepairingRoom) {
	EXPECT_TRUE(rm_test.roomInRepair("1d"));
	EXPECT_FALSE(rm_test.roomInRepair("1D"));
	EXPECT_TRUE(rm_test.roomInRepair("1E"));
	EXPECT_FALSE(rm_test.roomInRepair("1e"));
	EXPECT_FALSE(rm_test.roomInRepair("1A"));
	EXPECT_FALSE(rm_test.roomInRepair("2C"));
	EXPECT_TRUE(rm_test.roomInRepair("1E"));
}

TEST_F(RoomManagerTest, RoomRepaired) {
	EXPECT_TRUE(rm_test.roomRepaired("1D"));
	EXPECT_FALSE(rm_test.roomRepaired("1d"));
	EXPECT_FALSE(rm_test.roomRepaired("1A"));
	EXPECT_FALSE(rm_test.roomRepaired("2C"));
}

TEST_F(RoomManagerTest, ListAllAvailable) {
	std::vector<std::string> ava_rms = {
		"1B",
		"2B", "2C", "2D", "2E",
		"3A", "3B", "3C", "3D", "3E",
		"4A", "4B", "4C", "4D", "4E" };

	EXPECT_EQ(rm_test.listAllAvailableRooms(), ava_rms);
}