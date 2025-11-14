#include "../include/Section.h"

Section::Section() : sectionId(""), labName(""), courseCode(""), 
                     instructorId(""), roomId(""), semester("") {}

Section::Section(const string& id, const string& name, const string& code,
                const string& instId, const string& rmId, const string& sem)
    : sectionId(id), labName(name), courseCode(code), instructorId(instId), 
      roomId(rmId), semester(sem) {}

string Section::getSectionId() const {
    return sectionId;
}

string Section::getLabName() const {
    return labName;
}

string Section::getCourseCode() const {
    return courseCode;
}

string Section::getInstructorId() const {
    return instructorId;
}

vector<string> Section::getTaIds() const {
    return taIds;
}

string Section::getRoomId() const {
    return roomId;
}

string Section::getSemester() const {
    return semester;
}

void Section::setSectionId(const string& id) {
    sectionId = id;
}

void Section::setLabName(const string& name) {
    labName = name;
}

void Section::setCourseCode(const string& code) {
    courseCode = code;
}

void Section::setInstructorId(const string& instId) {
    instructorId = instId;
}

void Section::setRoomId(const string& rmId) {
    roomId = rmId;
}

void Section::setSemester(const string& sem) {
    semester = sem;
}

void Section::addTA(const string& taId) {
    if (find(taIds.begin(), taIds.end(), taId) == taIds.end()) {
        taIds.push_back(taId);
    }
}

void Section::removeTA(const string& taId) {
    taIds.erase(remove(taIds.begin(), taIds.end(), taId), taIds.end());
}

void Section::serialize(ofstream& out) const {
    size_t len = sectionId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(sectionId.c_str(), len);
    len = labName.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(labName.c_str(), len);
    len = courseCode.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(courseCode.c_str(), len);
    len = instructorId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(instructorId.c_str(), len);
    size_t taCount = taIds.size();
    out.write(reinterpret_cast<const char*>(&taCount), sizeof(taCount));
    for (const auto& taId : taIds) {
        len = taId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(taId.c_str(), len);
    }
    len = roomId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(roomId.c_str(), len);
    len = semester.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(semester.c_str(), len);
}

void Section::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    sectionId.resize(len);
    in.read(&sectionId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    labName.resize(len);
    in.read(&labName[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    courseCode.resize(len);
    in.read(&courseCode[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    instructorId.resize(len);
    in.read(&instructorId[0], len);
    size_t taCount;
    in.read(reinterpret_cast<char*>(&taCount), sizeof(taCount));
    taIds.clear();
    for (size_t i = 0; i < taCount; i++) {
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string taId;
        taId.resize(len);
        in.read(&taId[0], len);
        taIds.push_back(taId);
    }
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    roomId.resize(len);
    in.read(&roomId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    semester.resize(len);
    in.read(&semester[0], len);
}

ostream& operator<<(ostream& os, const Section& section) {
    os << section.sectionId << "|" << section.labName << "|" << section.courseCode 
       << "|" << section.instructorId << "|" << section.roomId << "|" << section.semester;
    return os;
}
