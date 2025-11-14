#include "../include/StorageManager.h"
#include <algorithm>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

const string StorageManager::DATA_DIR = "data/";
const string StorageManager::BUILDINGS_FILE = DATA_DIR + "buildings.dat";
const string StorageManager::ROOMS_FILE = DATA_DIR + "rooms.dat";
const string StorageManager::INSTRUCTORS_FILE = DATA_DIR + "instructors.dat";
const string StorageManager::TAS_FILE = DATA_DIR + "tas.dat";
const string StorageManager::SECTIONS_FILE = DATA_DIR + "sections.dat";
const string StorageManager::SESSIONS_FILE = DATA_DIR + "sessions.dat";
const string StorageManager::MAKEUP_REQUESTS_FILE = DATA_DIR + "makeup_requests.dat";

void StorageManager::ensureDataDir() {
#ifdef _WIN32
    _mkdir(DATA_DIR.c_str());
#else
    mkdir(DATA_DIR.c_str(), 0755);
#endif
}

void StorageManager::saveBuilding(const Building& building) {
    ensureDataDir();
    vector<Building> buildings = loadBuildings();
    buildings.erase(remove_if(buildings.begin(), buildings.end(),
        [&building](const Building& b) { return b.getBuildingId() == building.getBuildingId(); }),
        buildings.end());
    buildings.push_back(building);
    ofstream out(BUILDINGS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = buildings.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& b : buildings) {
            b.serialize(out);
        }
        out.close();
    }
}

vector<Building> StorageManager::loadBuildings() {
    vector<Building> buildings;
    ifstream in(BUILDINGS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            Building b;
            b.deserialize(in);
            buildings.push_back(b);
        }
        in.close();
    }
    return buildings;
}

Building* StorageManager::findBuilding(const string& buildingId) {
    static Building result;
    vector<Building> buildings = loadBuildings();
    for (auto& b : buildings) {
        if (b.getBuildingId() == buildingId) {
            result = b;
            return &result;
        }
    }
    return nullptr;
}

void StorageManager::saveRoom(const Room& room) {
    ensureDataDir();
    vector<Room> rooms = loadRooms();
    rooms.erase(remove_if(rooms.begin(), rooms.end(),
        [&room](const Room& r) { return r.getRoomId() == room.getRoomId(); }),
        rooms.end());
    rooms.push_back(room);
    ofstream out(ROOMS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = rooms.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& r : rooms) {
            r.serialize(out);
        }
        out.close();
    }
}

vector<Room> StorageManager::loadRooms() {
    vector<Room> rooms;
    ifstream in(ROOMS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            Room r;
            r.deserialize(in);
            rooms.push_back(r);
        }
        in.close();
    }
    return rooms;
}

Room* StorageManager::findRoom(const string& roomId) {
    static Room result;
    vector<Room> rooms = loadRooms();
    for (auto& r : rooms) {
        if (r.getRoomId() == roomId) {
            result = r;
            return &result;
        }
    }
    return nullptr;
}

vector<Room> StorageManager::findRoomsByBuilding(const string& buildingId) {
    vector<Room> rooms = loadRooms();
    vector<Room> result;
    for (const auto& r : rooms) {
        if (r.getBuildingId() == buildingId) {
            result.push_back(r);
        }
    }
    return result;
}

void StorageManager::saveInstructor(const Instructor& instructor) {
    ensureDataDir();
    vector<Instructor> instructors = loadInstructors();
    instructors.erase(remove_if(instructors.begin(), instructors.end(),
        [&instructor](const Instructor& i) { return i.getInstructorId() == instructor.getInstructorId(); }),
        instructors.end());
    instructors.push_back(instructor);
    ofstream out(INSTRUCTORS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = instructors.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& i : instructors) {
            i.serialize(out);
        }
        out.close();
    }
}

vector<Instructor> StorageManager::loadInstructors() {
    vector<Instructor> instructors;
    ifstream in(INSTRUCTORS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            Instructor inst;
            inst.deserialize(in);
            instructors.push_back(inst);
        }
        in.close();
    }
    return instructors;
}

Instructor* StorageManager::findInstructor(const string& instructorId) {
    static Instructor result;
    vector<Instructor> instructors = loadInstructors();
    for (auto& i : instructors) {
        if (i.getInstructorId() == instructorId) {
            result = i;
            return &result;
        }
    }
    return nullptr;
}

void StorageManager::saveTA(const TA& ta) {
    ensureDataDir();
    vector<TA> tas = loadTAs();
    tas.erase(remove_if(tas.begin(), tas.end(),
        [&ta](const TA& t) { return t.getTaId() == ta.getTaId(); }),
        tas.end());
    tas.push_back(ta);
    ofstream out(TAS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = tas.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& t : tas) {
            t.serialize(out);
        }
        out.close();
    }
}

vector<TA> StorageManager::loadTAs() {
    vector<TA> tas;
    ifstream in(TAS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            TA ta;
            ta.deserialize(in);
            tas.push_back(ta);
        }
        in.close();
    }
    return tas;
}

TA* StorageManager::findTA(const string& taId) {
    static TA result;
    vector<TA> tas = loadTAs();
    for (auto& t : tas) {
        if (t.getTaId() == taId) {
            result = t;
            return &result;
        }
    }
    return nullptr;
}

void StorageManager::saveSection(const Section& section) {
    ensureDataDir();
    vector<Section> sections = loadSections();
    sections.erase(remove_if(sections.begin(), sections.end(),
        [&section](const Section& s) { return s.getSectionId() == section.getSectionId(); }),
        sections.end());
    sections.push_back(section);
    ofstream out(SECTIONS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = sections.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& s : sections) {
            s.serialize(out);
        }
        out.close();
    }
}

vector<Section> StorageManager::loadSections() {
    vector<Section> sections;
    ifstream in(SECTIONS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            Section sec;
            sec.deserialize(in);
            sections.push_back(sec);
        }
        in.close();
    }
    return sections;
}

Section* StorageManager::findSection(const string& sectionId) {
    static Section result;
    vector<Section> sections = loadSections();
    for (auto& s : sections) {
        if (s.getSectionId() == sectionId) {
            result = s;
            return &result;
        }
    }
    return nullptr;
}

void StorageManager::saveSession(const LabSession& session) {
    ensureDataDir();
    vector<LabSession> sessions = loadSessions();
    sessions.erase(remove_if(sessions.begin(), sessions.end(),
        [&session](const LabSession& s) { return s.getSessionId() == session.getSessionId(); }),
        sessions.end());
    sessions.push_back(session);
    ofstream out(SESSIONS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = sessions.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& s : sessions) {
            s.serialize(out);
        }
        out.close();
    }
}

vector<LabSession> StorageManager::loadSessions() {
    vector<LabSession> sessions;
    ifstream in(SESSIONS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            LabSession sess;
            sess.deserialize(in);
            sessions.push_back(sess);
        }
        in.close();
    }
    return sessions;
}

vector<LabSession> StorageManager::findSessionsBySection(const string& sectionId) {
    vector<LabSession> allSessions = loadSessions();
    vector<LabSession> result;
    for (const auto& s : allSessions) {
        if (s.getSectionId() == sectionId) {
            result.push_back(s);
        }
    }
    return result;
}

vector<LabSession> StorageManager::findSessionsByWeek(const Date& weekStart) {
    vector<LabSession> allSessions = loadSessions();
    vector<LabSession> result;
    Date weekEnd = weekStart;
    weekEnd.day += 6;
    if (weekEnd.day > 31) {
        weekEnd.day -= 31;
        weekEnd.month++;
        if (weekEnd.month > 12) {
            weekEnd.month = 1;
            weekEnd.year++;
        }
    }
    for (const auto& s : allSessions) {
        Date sessionDate = s.getDate();
        if (!(sessionDate < weekStart) && (sessionDate < weekEnd || 
            (sessionDate.year == weekEnd.year && 
             sessionDate.month == weekEnd.month && 
             sessionDate.day == weekEnd.day))) {
            result.push_back(s);
        }
    }
    return result;
}

void StorageManager::saveMakeupRequest(const MakeupRequest& request) {
    ensureDataDir();
    vector<MakeupRequest> requests = loadMakeupRequests();
    requests.erase(remove_if(requests.begin(), requests.end(),
        [&request](const MakeupRequest& r) { return r.getRequestId() == request.getRequestId(); }),
        requests.end());
    requests.push_back(request);
    ofstream out(MAKEUP_REQUESTS_FILE, ios::binary);
    if (out.is_open()) {
        size_t count = requests.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& r : requests) {
            r.serialize(out);
        }
        out.close();
    }
}

vector<MakeupRequest> StorageManager::loadMakeupRequests() {
    vector<MakeupRequest> requests;
    ifstream in(MAKEUP_REQUESTS_FILE, ios::binary);
    if (in.is_open() && in.peek() != ifstream::traits_type::eof()) {
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            MakeupRequest req;
            req.deserialize(in);
            requests.push_back(req);
        }
        in.close();
    }
    return requests;
}

MakeupRequest* StorageManager::findMakeupRequest(const string& requestId) {
    static MakeupRequest result;
    vector<MakeupRequest> requests = loadMakeupRequests();
    for (auto& r : requests) {
        if (r.getRequestId() == requestId) {
            result = r;
            return &result;
        }
    }
    return nullptr;
}
