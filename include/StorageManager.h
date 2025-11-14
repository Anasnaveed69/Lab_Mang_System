#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "Building.h"
#include "Room.h"
#include "Instructor.h"
#include "TA.h"
#include "Section.h"
#include "LabSession.h"
#include "MakeupRequest.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class StorageManager {
private:
    static const string DATA_DIR;
    static const string BUILDINGS_FILE;
    static const string ROOMS_FILE;
    static const string INSTRUCTORS_FILE;
    static const string TAS_FILE;
    static const string SECTIONS_FILE;
    static const string SESSIONS_FILE;
    static const string MAKEUP_REQUESTS_FILE;
    static void ensureDataDir();

public:
    static void saveBuilding(const Building& building);
    static vector<Building> loadBuildings();
    static Building* findBuilding(const string& buildingId);
    static void saveRoom(const Room& room);
    static vector<Room> loadRooms();
    static Room* findRoom(const string& roomId);
    static vector<Room> findRoomsByBuilding(const string& buildingId);
    static void saveInstructor(const Instructor& instructor);
    static vector<Instructor> loadInstructors();
    static Instructor* findInstructor(const string& instructorId);
    static void saveTA(const TA& ta);
    static vector<TA> loadTAs();
    static TA* findTA(const string& taId);
    static void saveSection(const Section& section);
    static vector<Section> loadSections();
    static Section* findSection(const string& sectionId);
    static void saveSession(const LabSession& session);
    static vector<LabSession> loadSessions();
    static vector<LabSession> findSessionsBySection(const string& sectionId);
    static vector<LabSession> findSessionsByWeek(const Date& weekStart);
    static void saveMakeupRequest(const MakeupRequest& request);
    static vector<MakeupRequest> loadMakeupRequests();
    static MakeupRequest* findMakeupRequest(const string& requestId);
};

#endif
