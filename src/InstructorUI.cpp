#include "../include/InstructorUI.h"
#include "../include/StorageManager.h"
#include "../include/InputUtil.h"
#include "../include/MakeupRequest.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

string generateRequestId() {
    ostringstream oss;
    oss << "REQ_" << time(nullptr);
    return oss.str();
}

InstructorUI::InstructorUI(const string& instId) : instructorId(instId) {}

void InstructorUI::showMenu() {
    while (true) {
        cout << "\n=== Instructor Menu ===" << endl;
        cout << "1. Request Makeup Lab" << endl;
        cout << "2. View My Sections" << endl;
        cout << "3. View My Makeup Requests" << endl;
        cout << "0. Exit" << endl;
        int choice = InputUtil::readInt("Enter choice: ");
        switch (choice) {
            case 1: requestMakeupLab(); break;
            case 2: viewMySections(); break;
            case 3: viewMyMakeupRequests(); break;
            case 0: return;
            default: cout << "Invalid choice." << endl;
        }
    }
}

void InstructorUI::requestMakeupLab() {
    string sectionId = InputUtil::readString("Enter Section ID: ");
    Section* section = StorageManager::findSection(sectionId);
    if (section == nullptr) {
        cout << "Section not found!" << endl;
        return;
    }
    if (section->getInstructorId() != instructorId) {
        cout << "You don't have access to this section!" << endl;
        return;
    }
    Date requestedDate = InputUtil::readDate("Enter Date of Missed Lab");
    string reason = InputUtil::readString("Enter Reason: ");
    string requestId = generateRequestId();
    MakeupRequest request(requestId, sectionId, instructorId, requestedDate, reason);
    StorageManager::saveMakeupRequest(request);
    cout << "Makeup lab request submitted successfully!" << endl;
    cout << "Request ID: " << requestId << endl;
}

void InstructorUI::viewMySections() {
    vector<Section> allSections = StorageManager::loadSections();
    cout << "\n=== My Sections ===" << endl;
    for (const auto& section : allSections) {
        if (section.getInstructorId() == instructorId) {
            cout << section << endl;
        }
    }
}

void InstructorUI::viewMyMakeupRequests() {
    vector<MakeupRequest> allRequests = StorageManager::loadMakeupRequests();
    cout << "\n=== My Makeup Requests ===" << endl;
    for (const auto& request : allRequests) {
        if (request.getInstructorId() == instructorId) {
            cout << request << endl;
        }
    }
}
