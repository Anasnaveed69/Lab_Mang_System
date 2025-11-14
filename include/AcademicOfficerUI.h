#ifndef ACADEMICOFFICERUI_H
#define ACADEMICOFFICERUI_H

class AcademicOfficerUI {
public:
    void showMenu();
private:
    void addBuilding();
    void addRoom();
    void addInstructor();
    void addTA();
    void addSection();
    void scheduleLabSession();
    void viewBuildings();
    void viewRooms();
    void viewInstructors();
    void viewTAs();
    void viewSections();
    void viewMakeupRequests();
    void approveMakeupRequest();
};

#endif
