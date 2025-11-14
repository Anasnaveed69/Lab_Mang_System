#include "../include/AttendantUI.h"
#include "../include/StorageManager.h"
#include "../include/InputUtil.h"
#include <iostream>
#include <vector>
using namespace std;

AttendantUI::AttendantUI(const string& attId) : attendantId(attId) {}

void AttendantUI::showMenu() {
    while (true) {
        cout << "\n=== Attendant Menu ===" << endl;
        cout << "1. Fill Timesheet for Lab Session" << endl;
        cout << "2. View Sessions in My Building" << endl;
        cout << "0. Exit" << endl;
        int choice = InputUtil::readInt("Enter choice: ");
        switch (choice) {
            case 1: fillTimesheet(); break;
            case 2: viewSessionsInBuilding(); break;
            case 0: return;
            default: cout << "Invalid choice." << endl;
        }
    }
}

void AttendantUI::fillTimesheet() {
    string sessionId = InputUtil::readString("Enter Session ID: ");
    vector<LabSession> allSessions = StorageManager::loadSessions();
    LabSession* session = nullptr;
    for (auto& s : allSessions) {
        if (s.getSessionId() == sessionId) {
            session = &s;
            break;
        }
    }
    if (session == nullptr) {
        cout << "Session not found!" << endl;
        return;
    }
    Section* section = StorageManager::findSection(session->getSectionId());
    if (section == nullptr) {
        cout << "Section not found!" << endl;
        return;
    }
    Room* room = StorageManager::findRoom(section->getRoomId());
    if (room == nullptr) {
        cout << "Room not found!" << endl;
        return;
    }
    Building* building = StorageManager::findBuilding(room->getBuildingId());
    if (building == nullptr || building->getAttendantId() != attendantId) {
        cout << "You don't have access to this building!" << endl;
        return;
    }
    Time actualStart = InputUtil::readTime("Enter Actual Start Time");
    Time actualEnd = InputUtil::readTime("Enter Actual End Time");
    session->getTiming().setActualStart(actualStart);
    session->getTiming().setActualEnd(actualEnd);
    StorageManager::saveSession(*session);
    cout << "Timesheet filled successfully!" << endl;
}

void AttendantUI::viewSessionsInBuilding() {
    vector<Building> buildings = StorageManager::loadBuildings();
    Building* myBuilding = nullptr;
    for (auto& b : buildings) {
        if (b.getAttendantId() == attendantId) {
            myBuilding = &b;
            break;
        }
    }
    if (myBuilding == nullptr) {
        cout << "No building assigned to you!" << endl;
        return;
    }
    vector<Room> rooms = StorageManager::findRoomsByBuilding(myBuilding->getBuildingId());
    cout << "\n=== Sessions in " << myBuilding->getBuildingName() << " ===" << endl;
    vector<LabSession> allSessions = StorageManager::loadSessions();
    vector<Section> sections = StorageManager::loadSections();
    for (const auto& room : rooms) {
        for (const auto& section : sections) {
            if (section.getRoomId() == room.getRoomId()) {
                for (auto& session : allSessions) {
                    if (session.getSectionId() == section.getSectionId()) {
                        cout << "Session: " << session.getSessionId() 
                              << " | Date: " << session.getDate() 
                              << " | Room: " << room.getRoomNumber()
                              << " | Filled: " << (session.getTiming().isFilled() ? "Yes" : "No") 
                              << endl;
                    }
                }
            }
        }
    }
}
