
#include "RoomManager.h"



RoomManager::RoomManager() {
}

RoomManager::~RoomManager() {
}

bool RoomManager::addRoomToList(int flr, char sfx) {
	int h = getRoomIdHash(flr, sfx);
	if (rooms.find(h) != rooms.end())
		return false;

	rooms[h].hash = h;
	rooms[h].floor = flr;
	rooms[h].suffix = (char)std::toupper((int)sfx);
	rooms[h].state = eRoomState::AVAILABLE;
	rooms[h].populateRoomNumber();
	
	roomlists[eRoomState::AVAILABLE].insert(h);
	return true;
}

std::string RoomManager::requestAndAssignRoom() {
	std::string res;
	if (!roomlists[eRoomState::AVAILABLE].empty()) {
		const int h = (*roomlists[eRoomState::AVAILABLE].begin());
		if (changeRoomState(h, eRoomState::AVAILABLE, eRoomState::OCCUPIED)) {
			res = rooms[h].id;
		}
	}
	return res;
}

bool RoomManager::roomCheckout(std::string roomNum) {
	auto h = getRoomIdHash(roomNum);
	if (h > 0) {
		return changeRoomState(h, eRoomState::OCCUPIED, eRoomState::VACANT);
	}
	return false;
}

bool RoomManager::roomCleaned(std::string roomNum) {
	auto h = getRoomIdHash(roomNum);
	if (h > 0) {
		return changeRoomState(h, eRoomState::VACANT, eRoomState::AVAILABLE);
	}
	return false;
}

bool RoomManager::roomRepaired(std::string roomNum) {
	auto h = getRoomIdHash(roomNum);
	if (h > 0) {
		return changeRoomState(h, eRoomState::REPAIR, eRoomState::VACANT);
	}
	return false;
}

bool RoomManager::roomInRepair(std::string roomNum) {
	auto h = getRoomIdHash(roomNum);
	if (h > 0) {
		return changeRoomState(h, eRoomState::VACANT, eRoomState::REPAIR);
	}
	return false;
}

std::vector<std::string> RoomManager::listAllAvailableRooms() {
	std::vector<std::string> res;

	for (auto& r : roomlists[eRoomState::AVAILABLE]) {
		res.emplace_back(rooms[r].id);
	}

	return res;
}

int RoomManager::getRoomIdHash(const int flr, const char sfx) {
	int sfx_int = 0;
	switch(sfx) {
		case 'A':
			sfx_int = 1;
			break;
		case 'B':
			sfx_int = 2;
			break;
		case 'C':
			sfx_int = 3;
			break;
		case 'D':
			sfx_int = 4;
			break;
		case 'E':
			sfx_int = 5;
			break;
		default:
			break;
	}

	if (flr%2 == 0) {
		return ((flr * 10) + (6 - sfx_int));
	}
	return ((flr * 10) + sfx_int);
}

int RoomManager::getRoomIdHash(const std::string &roomNum) {
	size_t i = 0;
	for (; i < roomNum.length(); ++i) {
		if (isdigit(roomNum[i]))
			break;
	}

	std::string str = roomNum.substr(i, roomNum.length() - i);
	if (!str.empty()) {
		return std::atoi(str.c_str());
	}
	return -1;
}

bool RoomManager::changeRoomState(int rmId, eRoomState fromState, eRoomState toState) {
	if (rooms.count(rmId)) {
		if (!roomlists[fromState].erase(rmId))
			return false;

		roomlists[toState].insert(rmId);
		rooms[rmId].state = toState;
		return true;
	}
	return false;
}