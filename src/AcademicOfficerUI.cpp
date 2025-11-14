#include "../include/AcademicOfficerUI.h"
#include "../include/StorageManager.h"
#include "../include/InputUtil.h"
#include "../include/LabSession.h"
#include "../include/MakeupRequest.h"
#include <iostream>
using namespace std;

void AcademicOfficerUI::showMenu() {
    while (true) {
        cout << "\n=== Academic Officer Menu ===" << endl;
        cout << "1. Add Building" << endl;
        cout << "2. Add Room" << endl;
        cout << "3. Add Instructor" << endl;
        cout << "4. Add TA" << endl;
        cout << "5. Add Lab Section" << endl;
        cout << "6. Schedule Lab Session" << endl;
        cout << "7. View All Buildings" << endl;
        cout << "8. View All Rooms" << endl;
        cout << "9. View All Instructors" << endl;
        cout << "10. View All TAs" << endl;
        cout << "11. View All Sections" << endl;
        cout << "12. View Makeup Requests" << endl;
        cout << "13. Approve Makeup Request" << endl;
        cout << "0. Exit" << endl;
        int choice = InputUtil::readInt("Enter choice: ");
        switch (choice) {
            case 1: addBuilding(); break;
            case 2: addRoom(); break;
            case 3: addInstructor(); break;
            case 4: addTA(); break;
            case 5: addSection(); break;
            case 6: scheduleLabSession(); break;
            case 7: viewBuildings(); break;
            case 8: viewRooms(); break;
            case 9: viewInstructors(); break;
            case 10: viewTAs(); break;
            case 11: viewSections(); break;
            case 12: viewMakeupRequests(); break;
            case 13: approveMakeupRequest(); break;
            case 0: return;
            default: cout << "Invalid choice." << endl;
        }
    }
}

void AcademicOfficerUI::addBuilding() {
    string buildingId = InputUtil::readString("Enter Building ID: ");
    string buildingName = InputUtil::readString("Enter Building Name: ");
    string attendantId = InputUtil::readString("Enter Attendant ID: ");
    Building building(buildingId, buildingName, attendantId);
    StorageManager::saveBuilding(building);
    cout << "Building added successfully!" << endl;
}

void AcademicOfficerUI::addRoom() {
    string roomId = InputUtil::readString("Enter Room ID: ");
    string roomNumber = InputUtil::readString("Enter Room Number: ");
    string buildingId = InputUtil::readString("Enter Building ID: ");
    int capacity = InputUtil::readInt("Enter Capacity: ");
    Room room(roomId, roomNumber, buildingId, capacity);
    StorageManager::saveRoom(room);
    cout << "Room added successfully!" << endl;
}

void AcademicOfficerUI::addInstructor() {
    string instructorId = InputUtil::readString("Enter Instructor ID: ");
    string name = InputUtil::readString("Enter Name: ");
    string email = InputUtil::readString("Enter Email: ");
    string department = InputUtil::readString("Enter Department: ");
    Instructor instructor(instructorId, name, email, department);
    StorageManager::saveInstructor(instructor);
    cout << "Instructor added successfully!" << endl;
}

void AcademicOfficerUI::addTA() {
    string taId = InputUtil::readString("Enter TA ID: ");
    string name = InputUtil::readString("Enter Name: ");
    string email = InputUtil::readString("Enter Email: ");
    string studentId = InputUtil::readString("Enter Student ID: ");
    TA ta(taId, name, email, studentId);
    StorageManager::saveTA(ta);
    cout << "TA added successfully!" << endl;
}

void AcademicOfficerUI::addSection() {
    string sectionId = InputUtil::readString("Enter Section ID: ");
    string labName = InputUtil::readString("Enter Lab Name: ");
    string courseCode = InputUtil::readString("Enter Course Code: ");
    string instructorId = InputUtil::readString("Enter Instructor ID: ");
    string roomId = InputUtil::readString("Enter Room ID: ");
    string semester = InputUtil::readString("Enter Semester: ");
    Section section(sectionId, labName, courseCode, instructorId, roomId, semester);
    while (true) {
        string taId = InputUtil::readString("Enter TA ID (or 'done' to finish): ");
        if (taId == "done" || taId == "Done") {
            break;
        }
        section.addTA(taId);
    }
    StorageManager::saveSection(section);
    cout << "Section added successfully!" << endl;
}

void AcademicOfficerUI::scheduleLabSession() {
    string sessionId = InputUtil::readString("Enter Session ID: ");
    string sectionId = InputUtil::readString("Enter Section ID: ");
    Date date = InputUtil::readDate("Enter Date");
    int dayChoice = InputUtil::readDayOfWeek("Select Day of Week");
    Time expectedStart = InputUtil::readTime("Enter Expected Start Time");
    Time expectedEnd = InputUtil::readTime("Enter Expected End Time");
    LabSession session(sessionId, sectionId, date, expectedStart, expectedEnd);
    StorageManager::saveSession(session);
    cout << "Lab session scheduled successfully!" << endl;
}

void AcademicOfficerUI::viewBuildings() {
    vector<Building> buildings = StorageManager::loadBuildings();
    cout << "\n=== Buildings ===" << endl;
    for (const auto& b : buildings) {
        cout << b << endl;
    }
}

void AcademicOfficerUI::viewRooms() {
    vector<Room> rooms = StorageManager::loadRooms();
    cout << "\n=== Rooms ===" << endl;
    for (const auto& r : rooms) {
        cout << r << endl;
    }
}

void AcademicOfficerUI::viewInstructors() {
    vector<Instructor> instructors = StorageManager::loadInstructors();
    cout << "\n=== Instructors ===" << endl;
    for (const auto& i : instructors) {
        cout << i << endl;
    }
}

void AcademicOfficerUI::viewTAs() {
    vector<TA> tas = StorageManager::loadTAs();
    cout << "\n=== TAs ===" << endl;
    for (const auto& ta : tas) {
        cout << ta << endl;
    }
}

void AcademicOfficerUI::viewSections() {
    vector<Section> sections = StorageManager::loadSections();
    cout << "\n=== Sections ===" << endl;
    for (const auto& s : sections) {
        cout << s << endl;
    }
}

void AcademicOfficerUI::viewMakeupRequests() {
    vector<MakeupRequest> requests = StorageManager::loadMakeupRequests();
    cout << "\n=== Makeup Requests ===" << endl;
    for (const auto& request : requests) {
        cout << request << endl;
    }
}

void AcademicOfficerUI::approveMakeupRequest() {
    string requestId = InputUtil::readString("Enter Request ID: ");
    MakeupRequest* request = StorageManager::findMakeupRequest(requestId);
    if (request == nullptr) {
        cout << "Request not found!" << endl;
        return;
    }
    if (request->isApproved()) {
        cout << "Request already approved!" << endl;
        return;
    }
    Date makeupDate = InputUtil::readDate("Enter Makeup Date");
    request->setMakeupDate(makeupDate);
    request->setApproved(true);
    Section* section = StorageManager::findSection(request->getSectionId());
    if (section == nullptr) {
        cout << "Section not found!" << endl;
        return;
    }
    vector<LabSession> originalSessions = StorageManager::findSessionsBySection(request->getSectionId());
    LabSession* originalSession = nullptr;
    for (auto& s : originalSessions) {
        if (s.getDate().year == request->getRequestedDate().year &&
            s.getDate().month == request->getRequestedDate().month &&
            s.getDate().day == request->getRequestedDate().day) {
            originalSession = &s;
            break;
        }
    }
    if (originalSession == nullptr) {
        cout << "Original session not found!" << endl;
        return;
    }
    string sessionId = "MAKEUP_" + requestId;
    Time expStart = originalSession->getTiming().getExpectedStart();
    Time expEnd = originalSession->getTiming().getExpectedEnd();
    LabSession makeupSession(sessionId, request->getSectionId(), makeupDate, expStart, expEnd);
    makeupSession.setIsMakeup(true);
    StorageManager::saveSession(makeupSession);
    StorageManager::saveMakeupRequest(*request);
    cout << "Makeup request approved and session created!" << endl;
    cout << "Makeup Session ID: " << sessionId << endl;
}
