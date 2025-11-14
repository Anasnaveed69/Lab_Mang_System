#include "../include/Building.h"

Building::Building() : buildingId(""), buildingName(""), attendantId("") {}

Building::Building(const string& id, const string& name, const string& attId)
    : buildingId(id), buildingName(name), attendantId(attId) {}

string Building::getBuildingId() const {
    return buildingId;
}

string Building::getBuildingName() const {
    return buildingName;
}

string Building::getAttendantId() const {
    return attendantId;
}

void Building::setBuildingId(const string& id) {
    buildingId = id;
}

void Building::setBuildingName(const string& name) {
    buildingName = name;
}

void Building::setAttendantId(const string& attId) {
    attendantId = attId;
}

void Building::serialize(ofstream& out) const {
    size_t len = buildingId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(buildingId.c_str(), len);
    len = buildingName.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(buildingName.c_str(), len);
    len = attendantId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(attendantId.c_str(), len);
}

void Building::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buildingId.resize(len);
    in.read(&buildingId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buildingName.resize(len);
    in.read(&buildingName[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    attendantId.resize(len);
    in.read(&attendantId[0], len);
}

ostream& operator<<(ostream& os, const Building& building) {
    os << building.buildingId << "|" << building.buildingName << "|" << building.attendantId;
    return os;
}

