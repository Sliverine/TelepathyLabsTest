#pragma once

#include <set>
#include <unordered_set>
#include <map>
#include <vector>
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
	int id = -1; // used for internal sorting
	int floor = 0;
	char suffix = '\0';

	Room(eRoomState st) { state = st; };
};

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void addRoom(int flr, char sfx);
	Room requestNewRoom();
	bool roomCheckout(Room& rm);
	bool roomCleaned(Room& rm);
	bool roomRepaired(Room& rm);
	std::vector<Room> listAllAvailableRooms();
	
private:

	struct RoomList
	{
		bool sorted = false;
		union
		{
			std::set<Room> roomList_sorted;
			std::unordered_set<Room> roomList_unsorted;
		};
	};

	int generateRoomIdHash(int flr, char sfx);
	bool changeRoomState(Room& rm);

	std::map<eRoomState, RoomList> rooms;
};