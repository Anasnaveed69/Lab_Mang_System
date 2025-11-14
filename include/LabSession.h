#ifndef LABSESSION_H
#define LABSESSION_H

#include <string>
#include "Timing.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

struct Date {
    int year;
    int month;
    int day;
    Date() : year(2000), month(1), day(1) {}
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    int getDayOfWeek() const;
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d.year << "-" 
           << (d.month < 10 ? "0" : "") << d.month << "-"
           << (d.day < 10 ? "0" : "") << d.day;
        return os;
    }
    friend istream& operator>>(istream& is, Date& d) {
        char dash1, dash2;
        is >> d.year >> dash1 >> d.month >> dash2 >> d.day;
        return is;
    }
};

class LabSession {
private:
    string sessionId;
    string sectionId;
    Date date;
    int dayOfWeek;
    Timing timing;
    bool isMakeup;

public:
    LabSession();
    LabSession(const string& id, const string& secId, const Date& d, 
               const Time& expStart, const Time& expEnd);
    string getSessionId() const;
    string getSectionId() const;
    Date getDate() const;
    int getDayOfWeek() const;
    Timing& getTiming();
    const Timing& getTiming() const;
    bool getIsMakeup() const;
    void setSessionId(const string& id);
    void setSectionId(const string& secId);
    void setDate(const Date& d);
    void setIsMakeup(bool makeup);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const LabSession& session);
};

#endif
