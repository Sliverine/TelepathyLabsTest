#include "pch.h"


TEST_F(RoomManagerTest, HasRoom) {
	EXPECT_TRUE(rm_test.hasRoom("2b"));
	EXPECT_TRUE(rm_test.hasRoom("3B"));
	EXPECT_FALSE(rm_test.hasRoom("1A"));
	EXPECT_FALSE(rm_test.hasRoom("asdf"));
	EXPECT_FALSE(rm_test.hasRoom("1234"));
}

TEST_F(RoomManagerTest, AddRoom) {
	EXPECT_TRUE(rm_test.addNewRoom("1a"));
	EXPECT_FALSE(rm_test.addNewRoom("1A"));
	EXPECT_TRUE(rm_test.hasRoom("1A"));

	EXPECT_TRUE(rm_test.addNewRoom(1, 'e'));
	EXPECT_FALSE(rm_test.addNewRoom("1E"));
	EXPECT_TRUE(rm_test.hasRoom("1E"));
	// test edge cases
	EXPECT_FALSE(rm_test.addNewRoom("1234"));
	EXPECT_FALSE(rm_test.addNewRoom("abcd"));
	EXPECT_FALSE(rm_test.addNewRoom("1"));
	EXPECT_FALSE(rm_test.addNewRoom("b"));
	EXPECT_TRUE(rm_test.addNewRoom("11b"));
	EXPECT_FALSE(rm_test.addNewRoom("11bb"));

	EXPECT_FALSE(rm_test.addNewRoom(0, 'a'));
}

TEST_F(RoomManagerTest, RequestAndAssignRoom) {
	RoomManager rm_temp;
	EXPECT_EQ(rm_temp.requestAndAssignRoom(), "");

	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1B");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1C");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1D");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "2E");
}

TEST_F(RoomManagerTest, CheckoutRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();

	EXPECT_TRUE(rm_test.roomCheckout("1B"));
	EXPECT_FALSE(rm_test.roomCheckout("1b"));

	EXPECT_TRUE(rm_test.roomCheckout("1d"));
	EXPECT_FALSE(rm_test.roomCheckout("1D"));

	EXPECT_FALSE(rm_test.roomCheckout("3C"));
}

TEST_F(RoomManagerTest, CleanRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1B");

	EXPECT_TRUE(rm_test.roomCleaned("1b"));
	EXPECT_FALSE(rm_test.roomCleaned("1B"));
	EXPECT_FALSE(rm_test.roomCleaned("1C"));
	EXPECT_FALSE(rm_test.roomCleaned("4E"));
}

TEST_F(RoomManagerTest, RepairingRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1B");

	EXPECT_TRUE(rm_test.roomInRepair("1b"));
	EXPECT_FALSE(rm_test.roomInRepair("1B"));

	EXPECT_FALSE(rm_test.roomInRepair("1A"));
	EXPECT_FALSE(rm_test.roomInRepair("1C"));
	EXPECT_FALSE(rm_test.roomInRepair("2C"));
}

TEST_F(RoomManagerTest, RoomRepaired) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1B");
	rm_test.roomInRepair("1B");
	rm_test.roomCheckout("1C");

	EXPECT_TRUE(rm_test.roomRepaired("1b"));
	EXPECT_FALSE(rm_test.roomRepaired("1B"));

	EXPECT_FALSE(rm_test.roomRepaired("1A"));
	EXPECT_FALSE(rm_test.roomRepaired("1C"));
	EXPECT_FALSE(rm_test.roomRepaired("1D"));
}

TEST_F(RoomManagerTest, ListAllAvailable) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1C");
	rm_test.roomCleaned("1C");

	std::vector<std::string> ava_rms = {
		"1C",
		"2D", "2C", "2B", "2A",
		"3A", "3B", "3C", "3D", "3E",
		"4E", "4D", "4C", "4B", "4A" };

	EXPECT_EQ(rm_test.listAllAvailableRooms(), ava_rms);
}