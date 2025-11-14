#ifndef SECTION_H
#define SECTION_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Section {
private:
    string sectionId;
    string labName;
    string courseCode;
    string instructorId;
    vector<string> taIds;
    string roomId;
    string semester;

public:
    Section();
    Section(const string& id, const string& name, const string& code,
            const string& instId, const string& rmId, const string& sem);
    string getSectionId() const;
    string getLabName() const;
    string getCourseCode() const;
    string getInstructorId() const;
    vector<string> getTaIds() const;
    string getRoomId() const;
    string getSemester() const;
    void setSectionId(const string& id);
    void setLabName(const string& name);
    void setCourseCode(const string& code);
    void setInstructorId(const string& instId);
    void setRoomId(const string& rmId);
    void setSemester(const string& sem);
    void addTA(const string& taId);
    void removeTA(const string& taId);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const Section& section);
};

#endif
