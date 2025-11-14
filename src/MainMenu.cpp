#include "../include/MainMenu.h"
#include "../include/AcademicOfficerUI.h"
#include "../include/AttendantUI.h"
#include "../include/HeadOfDepartmentUI.h"
#include "../include/InstructorUI.h"
#include "../include/InputUtil.h"
#include <iostream>
using namespace std;

void MainMenu::showMainMenu() {
    while (true) {
        cout << "\n=== Labs Management System ===" << endl;
        cout << "1. Academic Officer" << endl;
        cout << "2. Attendant" << endl;
        cout << "3. Head of Department" << endl;
        cout << "4. Instructor" << endl;
        cout << "0. Exit" << endl;
        int choice = InputUtil::readInt("Enter choice: ");
        switch (choice) {
            case 1: {
                AcademicOfficerUI academicOfficerUI;
                academicOfficerUI.showMenu();
                break;
            }
            case 2: {
                string attendantId = InputUtil::readString("Enter Attendant ID: ");
                AttendantUI attendantUI(attendantId);
                attendantUI.showMenu();
                break;
            }
            case 3: {
                HeadOfDepartmentUI hodUI;
                hodUI.showMenu();
                break;
            }
            case 4: {
                string instructorId = InputUtil::readString("Enter Instructor ID: ");
                InstructorUI instructorUI(instructorId);
                instructorUI.showMenu();
                break;
            }
            case 0:
                cout << "Thank you for using Labs Management System!" << endl;
                return;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}
