
#include "RoomManager.h"

RoomManager::RoomManager() {
	rooms[eRoomState::AVAILABLE].sorted = true;
	rooms[eRoomState::OCCUPIED].sorted = false;
	rooms[eRoomState::VACANT].sorted = false;
	rooms[eRoomState::REPAIR].sorted = false;
}

RoomManager::~RoomManager() {
	
}

void RoomManager::addRoom(int flr, char sfx) {
	
}

Room RoomManager::requestNewRoom() {
	
}

bool RoomManager::roomCheckout(Room& rm) {
	
}

bool RoomManager::roomCleaned(Room& rm) {
	
}

bool RoomManager::roomRepaired(Room& rm) {
	
}

std::vector<Room> RoomManager::listAllAvailableRooms() {
	
}

int RoomManager::generateRoomIdHash(int flr, char sfx) {
	
}

bool RoomManager::changeRoomState(Room& rm) {
	
}