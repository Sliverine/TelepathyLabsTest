
#include "RoomManager.h"



RoomManager::RoomManager() {
	roomlists[eRoomState::AVAILABLE].isSorted = true;
}

RoomManager::~RoomManager() {
}

bool RoomManager::addNewRoom(int flr, char sfx) {
	int h = getRoomIdHash(flr, sfx);
	if (h < 0 || rooms.find(h) != rooms.end() || sfx == '\0')
		return false;

	rooms[h].hash = h;
	rooms[h].floor = flr;
	rooms[h].suffix = (char)std::toupper((int)sfx);
	rooms[h].state = eRoomState::AVAILABLE;
	rooms[h].populateRoomNumber();
	
	roomlists[eRoomState::AVAILABLE].addRoom(h);
	return true;
}

bool RoomManager::addNewRoom(std::string roomNum) {
	auto details = getRoomDetailsFromNum(roomNum);
	if (details.first < 0)
		return false;

	return addNewRoom(details.first, details.second);
}

bool RoomManager::hasRoomInList(std::string roomNum, eRoomState liststate) {
	int h = getRoomIdHash(roomNum);
	return roomlists[liststate].hasRoom(h);
}

bool RoomManager::hasRoom(std::string roomNum) {
	int h = getRoomIdHash(roomNum);
	return rooms.count(h);
}

std::string RoomManager::requestAndAssignRoom() {
	std::string res;
	auto h = roomlists[eRoomState::AVAILABLE].getNextRoom();
	if (h > 0 && changeRoomState(h, eRoomState::AVAILABLE, eRoomState::OCCUPIED)) {
		res = rooms[h].id;
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
	std::vector<std::string> res = {};
	auto rms = roomlists[eRoomState::AVAILABLE].getAllRooms();
	for (auto& r : rms) {
		res.emplace_back(rooms[r].id);
	}
	return res;
}

int RoomManager::getRoomIdHash(const int flr, const char sfx) {
	if (flr <= 0)
		return -1;

	int sfx_int = 0;
	char suf = (char)std::toupper((int)sfx);
	switch(suf) {
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
			return -1;
	}

	if (flr%2 == 0) {
		return ((flr * 10) + (6 - sfx_int));
	}
	return ((flr * 10) + sfx_int);
}

int RoomManager::getRoomIdHash(const std::string &roomNum) {
	auto details = getRoomDetailsFromNum(roomNum);
	if (details.first < 0)
		return -1;

	return getRoomIdHash(details.first, details.second);
}

std::pair<int, char> RoomManager::getRoomDetailsFromHash(int hash) {
	char c = '\0';
	if (hash <= 0) {
		return std::make_pair(-1, c);
	}

	int floor = hash / 10;
	int suf = hash % 10;
	
	bool inv = floor % 2 == 0;

	switch (suf) {
		case 1:
			inv ? c = 'E' : c = 'A';
			break;
		case 2:
			inv ? c = 'D' : c = 'B';
			break;
		case 3:
			inv ? c = 'C' : c = 'C';
			break;
		case 4:
			inv ? c = 'B' : c = 'D';
			break;
		case 5:
			inv ? c = 'A' : c = 'E';
			break;
		default:
			return std::make_pair(-1, c);
	}
	return std::make_pair(floor, c);
}

std::pair<int, char> RoomManager::getRoomDetailsFromNum(const std::string& roomNum) {
	size_t i = 0;
	char sfx = '\0';
	for (; i < roomNum.length(); ++i) {
		if (!std::isdigit(roomNum[i])) {
			sfx = (char)std::toupper((int)roomNum[i]);
			break;
		}
	}

	std::string str = roomNum.substr(0, i);
	if (!str.empty() && sfx != '\0') {
		int flr = std::atoi(str.c_str());
		return std::make_pair(flr, sfx);
	}
	return std::make_pair(-1, sfx);
}

bool RoomManager::changeRoomState(int rmHash, eRoomState fromState, eRoomState toState) {
	if (!rooms.count(rmHash) || !roomlists[fromState].hasRoom(rmHash)) {
		return false;
	}

	roomlists[fromState].rmvRoom(rmHash);
	roomlists[toState].addRoom(rmHash);
	rooms[rmHash].state = toState;
	return true;
}