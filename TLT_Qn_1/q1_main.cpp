#include <algorithm>
#include <iostream>
#include "RoomManager.h"

int main()
{
    RoomManager *mngr = new RoomManager();

    bool cont = true;
    std::string input;
    while(cont) {
        cout << "Welcome to Room Manager 101, please select choice:" << endl << endl;
        cout << "[1]   List available rooms" << endl;
        cout << "[2]   Make Room Reservation" << endl;
        cout << "[3]   Guest check out" << endl;
        cout << "[4]   Set room cleaned" << endl;
        cout << "[5]   Mark room in repair" << endl;
        cout << "[6]   Mark room finished repairs" << endl;
        cout << "[X]   Exit program" << endl << endl;
        cout << "Enter choice: ";
        cin >> input;

        const int choice = std::strtol(input.c_str(), NULL, 10);
        if (choice > 0 && choice < 7) {
            
        }
        else {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            if (input == "X") {
                cont = false;
                cout << endl << "Exit confirmed, goodbye!" << endl;
            }
            else {
                cout << endl << "Invalid input, please re-enter choice: " << endl;
            }
        }
    }

    delete mngr;
    return 0;
}