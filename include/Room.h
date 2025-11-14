#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Room {
private:
    string roomId;
    string roomNumber;
    string buildingId;
    int capacity;

public:
    Room();
    Room(const string& id, const string& number, const string& bldgId, int cap);
    string getRoomId() const;
    string getRoomNumber() const;
    string getBuildingId() const;
    int getCapacity() const;
    void setRoomId(const string& id);
    void setRoomNumber(const string& number);
    void setBuildingId(const string& bldgId);
    void setCapacity(int cap);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const Room& room);
};

#endif
