#pragma once

#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
using namespace std;

enum class eRoomState : int {
	UNDEFINED = 0,
	AVAILABLE = 1,
	OCCUPIED = 2,
	VACANT = 3,
	REPAIR = 4
};

struct Room {
	eRoomState state = eRoomState::UNDEFINED;
	int hash = -1; // used for internal sorting
	int floor = 0;
	char suffix = '\0';
	std::string id = "";
	
	void populateRoomNumber() {
		std::string res = std::to_string(floor) + suffix;
		id = res;
	}
	bool operator<(const Room& other) const {
		if (this->hash < other.hash)
			return true;
		return false;
	}
};

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	bool addNewRoom(int flr, char sfx);
	bool addNewRoom(std::string roomNum);
	bool hasRoomInList(std::string roomNum, eRoomState liststate);
	bool hasRoom(std::string roomNum);

	std::string requestAndAssignRoom();
	bool roomCheckout(std::string roomNum);
	bool roomCleaned(std::string roomNum);
	bool roomRepaired(std::string roomNum);
	bool roomInRepair(std::string roomNum);
	std::vector<std::string> listAllAvailableRooms();
	
protected:
	static int getRoomIdHash(const int flr, const char sfx);
	static int getRoomIdHash(const std::string &roomNum);
	static std::pair<int, char> getRoomDetailsFromHash(int hash);
	static std::pair<int, char> getRoomDetailsFromNum(const std::string& roomNum);
	bool changeRoomState(int rmHash, eRoomState fromState, eRoomState toState);

	struct RoomList
	{
		bool isSorted = false;
		std::set<int> sorted_list;
		std::unordered_set<int> list;

		void addRoom(int r) {
			if (isSorted)
				sorted_list.insert(r);
			else
				list.insert(r);
		}

		bool rmvRoom(int r) {
			return (isSorted ? sorted_list.erase(r) : list.erase(r));
		}

		int getNextRoom() {
			if (isSorted && !sorted_list.empty()) {
				return (*sorted_list.begin());
			}

			if (!isSorted && !list.empty()) {
				return (*list.begin());
			}
			return -1;
		}

		std::vector<int> getAllRooms() {
			std::vector<int> res = {};
			if (isSorted) {
				for (auto& x : sorted_list)
					res.emplace_back(x);
			}
			else {
				for (auto& x : list)
					res.emplace_back(x);
			}
			return res;
		}

		bool hasRoom(int r) {
			return (isSorted ? sorted_list.count(r) : list.count(r));
		}
	};

	std::unordered_map<int, Room> rooms;
	std::map<eRoomState, RoomList> roomlists;
};