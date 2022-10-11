//#include <algorithm>
//#include <iostream>
//#include "RoomManager.h"
//
//int main()
//{
//    RoomManager *mngr = new RoomManager();
//
//    // setup rooms
//
//
//    // start prog
//    bool cont = true;
//    std::string input;
//    while(cont) {
//        cout << "Welcome to Room Manager 101, please select choice:" << endl << endl;
//        cout << "[1]   List available rooms" << endl;
//        cout << "[2]   Make Room Reservation" << endl;
//        cout << "[3]   Guest check out" << endl;
//        cout << "[4]   Set room cleaned" << endl;
//        cout << "[5]   Mark room in repair" << endl;
//        cout << "[6]   Mark room finished repairs" << endl;
//        cout << "[X]   Exit program" << endl << endl;
//        cout << "Enter choice: ";
//        cin >> input;
//
//        const int choice = std::strtol(input.c_str(), NULL, 10);
//        if (choice > 0 && choice < 7) {
//            switch(choice) {
//                case 1: {
//                    auto lst = mngr->listAllAvailableRooms();
//
//                    if (lst.empty()) {
//                        cout << "No rooms available!";
//                    }
//                    else {
//                        int roomsPerLine = 5;
//                        int cnt = 0;
//                        cout << "\tList of available rooms:" << endl << "\t";
//                        for (auto& r : lst) {
//                            cout << r;
//                            if (cnt++ > roomsPerLine)
//                                cout << endl << "\t";
//                        }
//                        
//                    }
//                    cout << endl;
//                    break;
//                }
//                case 2: {
//                    auto rm = mngr->requestAndAssignRoom();
//                    if (!rm.empty()) {
//                        cout << "\tNearest room found: " << rm << endl;
//                        cout << "\tRoom " << rm << " has been booked!";
//                    }
//                    else {
//                        cout << "\tNo available rooms found!";
//                    }
//                    cout << endl;
//                    break;
//                }
//                case 3: {
//                    cout << "\tRoom number for check-out: ";
//                    input.clear();
//                    cin >> input;
//                    if (!mngr->hasRoom(input)) {
//                        cout << "\tRoom " << input << " does not exist!";
//                    }
//                    else {
//	                    if (mngr->roomCheckout(input)) {
//                            cout << "\tRoom " << input << " has been checked out successfully.";
//	                    }
//                        else {
//                            cout << "\tRoom " << input << " is not currently occupied.";
//                        }
//                    }
//                    cout << endl;
//                    break;
//                }
//                case 4: {
//                    cout << "\tRoom number to set available (cleaned): ";
//                    input.clear();
//                    cin >> input;
//                    if (!mngr->hasRoom(input)) {
//                        cout << "\tRoom " << input << " does not exist!";
//                    }
//                    else {
//                        if (mngr->roomCleaned(input)) {
//                            cout << "\tRoom " << input << " is cleaned and now available.";
//                        }
//                        else {
//                            cout << "\tRoom " << input << " was not vacant.";
//                        }
//                    }
//                    cout << endl;
//                    break;
//                }
//                case 5:
//                    cout << "\tRoom number in need of repair: ";
//                    input.clear();
//                    cin >> input;
//                    if (!mngr->hasRoom(input)) {
//                        cout << "\tRoom " << input << " does not exist!";
//                    }
//                    else {
//                        if (mngr->roomInRepair(input)) {
//                            cout << "\tRoom " << input << " is now marked as in repair.";
//                        }
//                        else {
//                            cout << "\tRoom " << input << " is not vacant.";
//                        }
//                    }
//                    cout << endl;
//                    break;
//                case 6:
//                    cout << "\tRoom number with repairs completed: ";
//                    input.clear();
//                    cin >> input;
//                    if (!mngr->hasRoom(input)) {
//                        cout << "\tRoom " << input << " does not exist!";
//                    }
//                    else {
//                        if (mngr->roomRepaired(input)) {
//                            cout << "\tRoom " << input << " is marked as vacant.";
//                        }
//                        else {
//                            cout << "\tRoom " << input << " was not in repair.";
//                        }
//                    }
//                    cout << endl;
//                    break;
//                default:
//                    break;
//            }
//        }
//        else {
//            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
//            if (input == "X") {
//                cont = false;
//                cout << endl << "Exit confirmed, goodbye!" << endl;
//            }
//            else {
//                cout << endl << "Invalid input, please re-enter choice: " << endl;
//            }
//        }
//    }
//
//    delete mngr;
//    return 0;
//}