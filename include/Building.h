#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Building {
private:
    string buildingId;
    string buildingName;
    string attendantId;

public:
    Building();
    Building(const string& id, const string& name, const string& attId);
    string getBuildingId() const;
    string getBuildingName() const;
    string getAttendantId() const;
    void setBuildingId(const string& id);
    void setBuildingName(const string& name);
    void setAttendantId(const string& attId);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const Building& building);
};

#endif

