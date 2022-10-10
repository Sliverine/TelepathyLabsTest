
#include "RoomManager.h"



RoomManager::RoomManager() {
}

RoomManager::~RoomManager() {
}

bool RoomManager::addRoomToList(int flr, char sfx) {
	int h = getRoomIdHash(flr, sfx);
	if (h < 0 || rooms.find(h) != rooms.end())
		return false;

	rooms[h].hash = h;
	rooms[h].floor = flr;
	rooms[h].suffix = (char)std::toupper((int)sfx);
	rooms[h].state = eRoomState::AVAILABLE;
	rooms[h].populateRoomNumber();
	
	roomlists[eRoomState::AVAILABLE].s_list.insert(h);
	return true;
}

bool RoomManager::addRoomToList(std::string roomNum) {
	int h = getRoomIdHash(roomNum);
	if (h < 0 || rooms.find(h) != rooms.end())
		return false;

	auto rmDetails = getRoomNumFromHash(h);
	return addRoomToList(rmDetails.first, rmDetails.second);
}

std::string RoomManager::requestAndAssignRoom() {
	std::string res;
	if (!roomlists[eRoomState::AVAILABLE].s_list.empty()) {
		const int h = (*roomlists[eRoomState::AVAILABLE].s_list.begin());
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

	for (auto& r : roomlists[eRoomState::AVAILABLE].s_list) {
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
			return -1;
	}

	if (flr%2 == 0) {
		return ((flr * 10) + (6 - sfx_int));
	}
	return ((flr * 10) + sfx_int);
}

int RoomManager::getRoomIdHash(const std::string &roomNum) {
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
		return getRoomIdHash(flr, sfx);
	}
	return -1;
}

std::pair<int, char> RoomManager::getRoomNumFromHash(int hash) {
	int floor = hash / 10;
	int suf = hash % 10;
	char c = '\0';
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

bool RoomManager::changeRoomState(int rmId, eRoomState fromState, eRoomState toState) {
	if (rooms.count(rmId)) {

		if (roomlists[fromState].isSorted) {
			if (!roomlists[fromState].s_list.erase(rmId))
				return false;
		}
		else {
			if (!roomlists[fromState].u_list.erase(rmId))
				return false;
		}

		if (roomlists[toState].isSorted)
			roomlists[toState].s_list.insert(rmId);
		else
			roomlists[toState].u_list.insert(rmId);

		rooms[rmId].state = toState;
		return true;
	}
	return false;
}