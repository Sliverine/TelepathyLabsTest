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

	bool addRoomToList(int flr, char sfx);
	bool addRoomToList(std::string roomNum);
	bool hasRoomInList(std::string roomNum, eRoomState liststate);
	bool hasRoom(std::string roomNum);

	std::string requestAndAssignRoom();
	bool roomCheckout(std::string roomNum);
	bool roomCleaned(std::string roomNum);
	bool roomRepaired(std::string roomNum);
	bool roomInRepair(std::string roomNum);
	std::vector<std::string> listAllAvailableRooms();
	
private:
	static int getRoomIdHash(const int flr, const char sfx);
	static int getRoomIdHash(const std::string &roomNum);
	static std::pair<int, char> getRoomDetailsFromHash(int hash);
	static std::pair<int, char> getRoomDetailsFromNum(const std::string& roomNum);
	bool changeRoomState(int rmId, eRoomState fromState, eRoomState toState);

	struct RoomList
	{
		bool isSorted = false;
		union
		{
			std::unordered_set<int> u_list;
			std::set<int> s_list;
		};
	};

	std::unordered_map<int, Room> rooms;
	std::map<eRoomState, RoomList> roomlists;
};