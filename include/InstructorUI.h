#ifndef INSTRUCTORUI_H
#define INSTRUCTORUI_H

#include <string>
using namespace std;

class InstructorUI {
private:
    string instructorId;
public:
    InstructorUI(const string& instId);
    void showMenu();
private:
    void requestMakeupLab();
    void viewMySections();
    void viewMyMakeupRequests();
};

#endif
