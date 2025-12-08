#ifndef HEADOFDEPARTMENTUI_H
#define HEADOFDEPARTMENTUI_H

#include <vector>
#include <string>
using namespace std;

class LabSession;
class Section;
class Instructor;
class Room;

class HeadOfDepartmentUI {
public:
    void showMenu();
private:
    void generateWeeklySchedule();
    void generateWeeklyTimesheet();
    void generateLabSectionTimesheet();
    
    // Helper methods to reduce code duplication
    static void sortSessionsByDate(vector<LabSession>& sessions);
    static Section* findSectionById(const string& sectionId, vector<Section>& sections);
    struct SessionDetails {
        Section* section;
        Instructor* instructor;
        Room* room;
    };
    static SessionDetails getSessionDetails(const LabSession& session, vector<Section>& sections);
};

#endif
