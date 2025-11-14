#include "../include/Room.h"

Room::Room() : roomId(""), roomNumber(""), buildingId(""), capacity(0) {}

Room::Room(const string& id, const string& number, const string& bldgId, int cap)
    : roomId(id), roomNumber(number), buildingId(bldgId), capacity(cap) {}

string Room::getRoomId() const {
    return roomId;
}

string Room::getRoomNumber() const {
    return roomNumber;
}

string Room::getBuildingId() const {
    return buildingId;
}

int Room::getCapacity() const {
    return capacity;
}

void Room::setRoomId(const string& id) {
    roomId = id;
}

void Room::setRoomNumber(const string& number) {
    roomNumber = number;
}

void Room::setBuildingId(const string& bldgId) {
    buildingId = bldgId;
}

void Room::setCapacity(int cap) {
    capacity = cap;
}

void Room::serialize(ofstream& out) const {
    size_t len = roomId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(roomId.c_str(), len);
    len = roomNumber.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(roomNumber.c_str(), len);
    len = buildingId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(buildingId.c_str(), len);
    out.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
}

void Room::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    roomId.resize(len);
    in.read(&roomId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    roomNumber.resize(len);
    in.read(&roomNumber[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buildingId.resize(len);
    in.read(&buildingId[0], len);
    in.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
}

ostream& operator<<(ostream& os, const Room& room) {
    os << room.roomId << "|" << room.roomNumber << "|" << room.buildingId << "|" << room.capacity;
    return os;
}
