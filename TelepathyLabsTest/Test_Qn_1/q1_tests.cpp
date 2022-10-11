#include "pch.h"


TEST_F(RoomManagerTest, HasRoom) {
	// test hasRoom fn with correct and wrong input
	EXPECT_TRUE(rm_test.hasRoom("2b"));
	EXPECT_TRUE(rm_test.hasRoom("3B"));
	EXPECT_FALSE(rm_test.hasRoom("1A"));
	EXPECT_FALSE(rm_test.hasRoom("asdf"));
	EXPECT_FALSE(rm_test.hasRoom("1234"));
}

TEST_F(RoomManagerTest, AddRoom) {
	// test variant 1 of add room fn
	EXPECT_TRUE(rm_test.addNewRoom("1a"));
	EXPECT_FALSE(rm_test.addNewRoom("1A"));
	EXPECT_TRUE(rm_test.hasRoom("1A"));
	// test variant 2 of add room fn
	EXPECT_TRUE(rm_test.addNewRoom(1, 'e'));
	EXPECT_FALSE(rm_test.addNewRoom("1E"));
	EXPECT_TRUE(rm_test.hasRoom("1E"));
	// test edge cases for string input for variant 1
	EXPECT_FALSE(rm_test.addNewRoom("1234"));
	EXPECT_FALSE(rm_test.addNewRoom("abcd"));
	EXPECT_FALSE(rm_test.addNewRoom("1"));
	EXPECT_FALSE(rm_test.addNewRoom("b"));
	EXPECT_TRUE(rm_test.addNewRoom("11b"));
	EXPECT_FALSE(rm_test.addNewRoom("11bb"));
	// test edge cases for variant 2
	EXPECT_FALSE(rm_test.addNewRoom(0, 'a'));
	EXPECT_FALSE(rm_test.addNewRoom(-2, 'e'));
}

TEST_F(RoomManagerTest, RequestAndAssignRoom) {
	// test empty case with no rooms inited
	RoomManager rm_temp;
	EXPECT_EQ(rm_temp.requestAndAssignRoom(), "");
	// test std functionality
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1B");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1C");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1D");
	// test next room assigned always nearest
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "2E");
	// extra test for nearest assignment
	rm_test.roomCheckout("1C");
	rm_test.roomCleaned("1C");
	EXPECT_EQ(rm_test.requestAndAssignRoom(), "1C");
}

TEST_F(RoomManagerTest, CheckoutRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	// test correct & incorrect checkout as well as string input invariance
	EXPECT_TRUE(rm_test.roomCheckout("1B"));
	EXPECT_FALSE(rm_test.roomCheckout("1b"));

	EXPECT_TRUE(rm_test.roomCheckout("1d"));
	EXPECT_FALSE(rm_test.roomCheckout("1D"));
	// test invalid checkout
	EXPECT_FALSE(rm_test.roomCheckout("3C"));
}

TEST_F(RoomManagerTest, CleanRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1B");
	// test correct & incorrect room clean
	EXPECT_TRUE(rm_test.roomCleaned("1b"));
	EXPECT_FALSE(rm_test.roomCleaned("1B"));
	// test invalid room clean
	EXPECT_FALSE(rm_test.roomCleaned("1C"));
	EXPECT_FALSE(rm_test.roomCleaned("4E"));
}

TEST_F(RoomManagerTest, RepairingRoom) {
	rm_test.requestAndAssignRoom();
	rm_test.requestAndAssignRoom();
	rm_test.roomCheckout("1B");
	// test correct & incorrect room repair
	EXPECT_TRUE(rm_test.roomInRepair("1b"));
	EXPECT_FALSE(rm_test.roomInRepair("1B"));
	// test invalid room repair
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
	// test correct & incorrect room repaired
	EXPECT_TRUE(rm_test.roomRepaired("1b"));
	EXPECT_FALSE(rm_test.roomRepaired("1B"));
	// test invalid room repaired
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
	// test correct listing operation
	EXPECT_EQ(rm_test.listAllAvailableRooms(), ava_rms);
}