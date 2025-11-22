#include "../include/HeadOfDepartmentUI.h"
#include "../include/StorageManager.h"
#include "../include/InputUtil.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

void HeadOfDepartmentUI::showMenu() {
    while (true) {
        cout << "\n=== Head of Department Menu ===" << endl;
        cout << "1. Generate Complete Lab Schedule for Week" << endl;
        cout << "2. Generate Filled Timesheet for Week" << endl;
        cout << "3. Generate Timesheet for Lab Section (All Sessions)" << endl;
        cout << "0. Exit" << endl;
        int choice = InputUtil::readInt("Enter choice: ");
        switch (choice) {
            case 1: generateWeeklySchedule(); break;
            case 2: generateWeeklyTimesheet(); break;
            case 3: generateLabSectionTimesheet(); break;
            case 0: return;
            default: cout << "Invalid choice." << endl;
        }
    }
}

void HeadOfDepartmentUI::generateWeeklySchedule() {
    Date weekStart = InputUtil::readDate("Enter Week Start Date");
    vector<LabSession> sessions = StorageManager::findSessionsByWeek(weekStart);
    
    // Sort sessions by date for better readability
    sort(sessions.begin(), sessions.end(), [](const LabSession& a, const LabSession& b) {
        Date dateA = a.getDate();
        Date dateB = b.getDate();
        if (dateA.year != dateB.year) return dateA.year < dateB.year;
        if (dateA.month != dateB.month) return dateA.month < dateB.month;
        return dateA.day < dateB.day;
    });
    
    vector<Section> sections = StorageManager::loadSections();
    vector<Instructor> instructors = StorageManager::loadInstructors();
    vector<Room> rooms = StorageManager::loadRooms();
    cout << "\n=== Complete Lab Schedule for Week Starting " << weekStart << " ===" << endl;
    cout << left << setw(15) << "Session ID" 
         << setw(20) << "Lab Name" 
         << setw(15) << "Date" 
         << setw(15) << "Day" 
         << setw(15) << "Start" 
         << setw(15) << "End" 
         << setw(15) << "Instructor" 
         << setw(15) << "Room" << endl;
    cout << string(120, '-') << endl;
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (const auto& session : sessions) {
        Section* section = nullptr;
        for (auto& s : sections) {
            if (s.getSectionId() == session.getSectionId()) {
                section = &s;
                break;
            }
        }
        if (section == nullptr) continue;
        Instructor* instructor = StorageManager::findInstructor(section->getInstructorId());
        Room* room = StorageManager::findRoom(section->getRoomId());
        cout << left << setw(15) << session.getSessionId()
             << setw(20) << section->getLabName()
             << setw(15) << session.getDate()
             << setw(15) << days[session.getDayOfWeek()]
             << setw(15) << session.getTiming().getExpectedStart()
             << setw(15) << session.getTiming().getExpectedEnd()
             << setw(15) << (instructor != nullptr ? instructor->getName() : "N/A")
             << setw(15) << (room != nullptr ? room->getRoomNumber() : "N/A") << endl;
    }
}

void HeadOfDepartmentUI::generateWeeklyTimesheet() {
    Date weekStart = InputUtil::readDate("Enter Week Start Date");
    vector<LabSession> sessions = StorageManager::findSessionsByWeek(weekStart);
    
    // Sort sessions by date
    sort(sessions.begin(), sessions.end(), [](const LabSession& a, const LabSession& b) {
        Date dateA = a.getDate();
        Date dateB = b.getDate();
        if (dateA.year != dateB.year) return dateA.year < dateB.year;
        if (dateA.month != dateB.month) return dateA.month < dateB.month;
        return dateA.day < dateB.day;
    });
    
    vector<Section> sections = StorageManager::loadSections();
    vector<Instructor> instructors = StorageManager::loadInstructors();
    vector<Room> rooms = StorageManager::loadRooms();
    cout << "\n=== Filled Timesheet for Week Starting " << weekStart << " ===" << endl;
    cout << left << setw(15) << "Session ID" 
         << setw(20) << "Lab Name" 
         << setw(15) << "Date" 
         << setw(15) << "Expected" 
         << setw(15) << "Actual" 
         << setw(15) << "Instructor" 
         << setw(15) << "Room" 
         << setw(10) << "Hours" << endl;
    cout << string(120, '-') << endl;
    for (const auto& session : sessions) {
        if (!session.getTiming().isFilled()) {
            continue;
        }
        Section* section = nullptr;
        for (auto& s : sections) {
            if (s.getSectionId() == session.getSectionId()) {
                section = &s;
                break;
            }
        }
        if (section == nullptr) continue;
        Instructor* instructor = StorageManager::findInstructor(section->getInstructorId());
        Room* room = StorageManager::findRoom(section->getRoomId());
        ostringstream expected, actual;
        expected << session.getTiming().getExpectedStart() << "-" << session.getTiming().getExpectedEnd();
        actual << session.getTiming().getActualStart() << "-" << session.getTiming().getActualEnd();
        cout << left << setw(15) << session.getSessionId()
             << setw(20) << section->getLabName()
             << setw(15) << session.getDate()
             << setw(15) << expected.str()
             << setw(15) << actual.str()
             << setw(15) << (instructor != nullptr ? instructor->getName() : "N/A")
             << setw(15) << (room != nullptr ? room->getRoomNumber() : "N/A")
             << setw(10) << fixed << setprecision(2) << session.getTiming().getContactHours() << endl;
    }
}

void HeadOfDepartmentUI::generateLabSectionTimesheet() {
    string sectionId = InputUtil::readString("Enter Section ID: ");
    vector<LabSession> sessions = StorageManager::findSessionsBySection(sectionId);
    
    // Sort sessions by date
    sort(sessions.begin(), sessions.end(), [](const LabSession& a, const LabSession& b) {
        Date dateA = a.getDate();
        Date dateB = b.getDate();
        if (dateA.year != dateB.year) return dateA.year < dateB.year;
        if (dateA.month != dateB.month) return dateA.month < dateB.month;
        return dateA.day < dateB.day;
    });
    
    Section* section = StorageManager::findSection(sectionId);
    if (section == nullptr) {
        cout << "Section not found!" << endl;
        return;
    }
    Instructor* instructor = StorageManager::findInstructor(section->getInstructorId());
    cout << "\n=== Timesheet for Lab Section: " << section->getLabName() << " ===" << endl;
    cout << "Course Code: " << section->getCourseCode() << endl;
    cout << "Semester: " << section->getSemester() << endl;
    cout << "Instructor: " << (instructor != nullptr ? instructor->getName() : "N/A") << endl;
    cout << endl;
    cout << left << setw(15) << "Session ID" 
         << setw(15) << "Date" 
         << setw(15) << "Day" 
         << setw(15) << "Expected" 
         << setw(15) << "Actual" 
         << setw(10) << "Hours" 
         << setw(10) << "Makeup" << endl;
    cout << string(95, '-') << endl;
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    double totalContactHours = 0.0;
    int totalSessions = 0;
    int filledSessions = 0;
    int makeupSessions = 0;
    for (const auto& session : sessions) {
        ostringstream expected, actual;
        expected << session.getTiming().getExpectedStart() << "-" << session.getTiming().getExpectedEnd();
        if (session.getTiming().isFilled()) {
            actual << session.getTiming().getActualStart() << "-" << session.getTiming().getActualEnd();
        } else {
            actual << "Not Filled";
        }
        double hours = session.getTiming().getContactHours();
        totalContactHours += hours;
        totalSessions++;
        if (session.getTiming().isFilled()) {
            filledSessions++;
        }
        if (session.getIsMakeup()) {
            makeupSessions++;
        }
        cout << left << setw(15) << session.getSessionId()
             << setw(15) << session.getDate()
             << setw(15) << days[session.getDayOfWeek()]
             << setw(15) << expected.str()
             << setw(15) << actual.str()
             << setw(10) << fixed << setprecision(2) << hours
             << setw(10) << (session.getIsMakeup() ? "Yes" : "No") << endl;
    }
    int leaves = totalSessions - filledSessions;
    cout << "\n=== Summary ===" << endl;
    cout << "Total Sessions: " << totalSessions << endl;
    cout << "Filled Sessions: " << filledSessions << endl;
    cout << "Leaves: " << leaves << endl;
    cout << "Makeup Sessions: " << makeupSessions << endl;
    cout << "Total Contact Hours: " << fixed << setprecision(2) << totalContactHours << endl;
}
