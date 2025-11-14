#ifndef ATTENDANTUI_H
#define ATTENDANTUI_H

#include <string>
using namespace std;

class AttendantUI {
private:
    string attendantId;
public:
    AttendantUI(const string& attId);
    void showMenu();
private:
    void fillTimesheet();
    void viewSessionsInBuilding();
};

#endif
