#ifndef TIMING_H
#define TIMING_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Time {
    int hour;
    int minute;
    Time() : hour(0), minute(0) {}
    Time(int h, int m) : hour(h), minute(m) {}
    double toHours() const {
        return hour + minute / 60.0;
    }
    int toMinutes() const {
        return hour * 60 + minute;
    }
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << (t.hour < 10 ? "0" : "") << t.hour << ":" 
           << (t.minute < 10 ? "0" : "") << t.minute;
        return os;
    }
    friend istream& operator>>(istream& is, Time& t) {
        char colon;
        is >> t.hour >> colon >> t.minute;
        return is;
    }
};

class Timing {
private:
    Time expectedStart;
    Time expectedEnd;
    Time actualStart;
    Time actualEnd;
    bool actualStartSet;
    bool actualEndSet;

public:
    Timing();
    Timing(const Time& expStart, const Time& expEnd);
    Time getExpectedStart() const;
    Time getExpectedEnd() const;
    Time getActualStart() const;
    Time getActualEnd() const;
    bool isFilled() const;
    void setExpectedStart(const Time& t);
    void setExpectedEnd(const Time& t);
    void setActualStart(const Time& t);
    void setActualEnd(const Time& t);
    double getContactHours() const;
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const Timing& timing);
};

#endif
