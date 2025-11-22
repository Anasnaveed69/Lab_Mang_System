#include "../include/Timing.h"

Timing::Timing() : expectedStart(), expectedEnd(), actualStart(), actualEnd(), 
                   actualStartSet(false), actualEndSet(false) {}

Timing::Timing(const Time& expStart, const Time& expEnd)
    : expectedStart(expStart), expectedEnd(expEnd), actualStart(), actualEnd(),
      actualStartSet(false), actualEndSet(false) {}

Time Timing::getExpectedStart() const {
    return expectedStart;
}

Time Timing::getExpectedEnd() const {
    return expectedEnd;
}

Time Timing::getActualStart() const {
    return actualStart;
}

Time Timing::getActualEnd() const {
    return actualEnd;
}

bool Timing::isFilled() const {
    return actualStartSet && actualEndSet;
}

void Timing::setExpectedStart(const Time& t) {
    expectedStart = t;
}

void Timing::setExpectedEnd(const Time& t) {
    expectedEnd = t;
}

void Timing::setActualStart(const Time& t) {
    actualStart = t;
    actualStartSet = true;
}

void Timing::setActualEnd(const Time& t) {
    actualEnd = t;
    actualEndSet = true;
}

double Timing::getContactHours() const {
    if (actualStartSet && actualEndSet) {
        int startMinutes = actualStart.toMinutes();
        int endMinutes = actualEnd.toMinutes();
        int diff = endMinutes - startMinutes;
        // Safety check: if end is before start, return 0 (invalid data)
        if (diff < 0) {
            return 0.0;
        }
        return diff / 60.0;
    }
    return 0.0;
}

void Timing::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&expectedStart.hour), sizeof(int));
    out.write(reinterpret_cast<const char*>(&expectedStart.minute), sizeof(int));
    out.write(reinterpret_cast<const char*>(&expectedEnd.hour), sizeof(int));
    out.write(reinterpret_cast<const char*>(&expectedEnd.minute), sizeof(int));
    out.write(reinterpret_cast<const char*>(&actualStart.hour), sizeof(int));
    out.write(reinterpret_cast<const char*>(&actualStart.minute), sizeof(int));
    out.write(reinterpret_cast<const char*>(&actualEnd.hour), sizeof(int));
    out.write(reinterpret_cast<const char*>(&actualEnd.minute), sizeof(int));
    out.write(reinterpret_cast<const char*>(&actualStartSet), sizeof(bool));
    out.write(reinterpret_cast<const char*>(&actualEndSet), sizeof(bool));
}

void Timing::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&expectedStart.hour), sizeof(int));
    in.read(reinterpret_cast<char*>(&expectedStart.minute), sizeof(int));
    in.read(reinterpret_cast<char*>(&expectedEnd.hour), sizeof(int));
    in.read(reinterpret_cast<char*>(&expectedEnd.minute), sizeof(int));
    in.read(reinterpret_cast<char*>(&actualStart.hour), sizeof(int));
    in.read(reinterpret_cast<char*>(&actualStart.minute), sizeof(int));
    in.read(reinterpret_cast<char*>(&actualEnd.hour), sizeof(int));
    in.read(reinterpret_cast<char*>(&actualEnd.minute), sizeof(int));
    in.read(reinterpret_cast<char*>(&actualStartSet), sizeof(bool));
    in.read(reinterpret_cast<char*>(&actualEndSet), sizeof(bool));
}

ostream& operator<<(ostream& os, const Timing& timing) {
    os << timing.expectedStart << "-" << timing.expectedEnd;
    if (timing.isFilled()) {
        os << " (" << timing.actualStart << "-" << timing.actualEnd << ")";
    }
    return os;
}
