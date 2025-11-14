#include "../include/LabSession.h"
#include <ctime>

int Date::getDayOfWeek() const {
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 12;
    time_t t = mktime(&timeinfo);
    struct tm* timeinfo2 = localtime(&t);
    return timeinfo2->tm_wday;
}

LabSession::LabSession() : sessionId(""), sectionId(""), date(), dayOfWeek(0), 
                           timing(), isMakeup(false) {}

LabSession::LabSession(const string& id, const string& secId, const Date& d,
                       const Time& expStart, const Time& expEnd)
    : sessionId(id), sectionId(secId), date(d), timing(expStart, expEnd), isMakeup(false) {
    dayOfWeek = date.getDayOfWeek();
}

string LabSession::getSessionId() const {
    return sessionId;
}

string LabSession::getSectionId() const {
    return sectionId;
}

Date LabSession::getDate() const {
    return date;
}

int LabSession::getDayOfWeek() const {
    return dayOfWeek;
}

Timing& LabSession::getTiming() {
    return timing;
}

const Timing& LabSession::getTiming() const {
    return timing;
}

bool LabSession::getIsMakeup() const {
    return isMakeup;
}

void LabSession::setSessionId(const string& id) {
    sessionId = id;
}

void LabSession::setSectionId(const string& secId) {
    sectionId = secId;
}

void LabSession::setDate(const Date& d) {
    date = d;
    dayOfWeek = date.getDayOfWeek();
}

void LabSession::setIsMakeup(bool makeup) {
    isMakeup = makeup;
}

void LabSession::serialize(ofstream& out) const {
    size_t len = sessionId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(sessionId.c_str(), len);
    len = sectionId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(sectionId.c_str(), len);
    out.write(reinterpret_cast<const char*>(&date.year), sizeof(int));
    out.write(reinterpret_cast<const char*>(&date.month), sizeof(int));
    out.write(reinterpret_cast<const char*>(&date.day), sizeof(int));
    out.write(reinterpret_cast<const char*>(&dayOfWeek), sizeof(int));
    timing.serialize(out);
    out.write(reinterpret_cast<const char*>(&isMakeup), sizeof(bool));
}

void LabSession::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    sessionId.resize(len);
    in.read(&sessionId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    sectionId.resize(len);
    in.read(&sectionId[0], len);
    in.read(reinterpret_cast<char*>(&date.year), sizeof(int));
    in.read(reinterpret_cast<char*>(&date.month), sizeof(int));
    in.read(reinterpret_cast<char*>(&date.day), sizeof(int));
    in.read(reinterpret_cast<char*>(&dayOfWeek), sizeof(int));
    timing.deserialize(in);
    in.read(reinterpret_cast<char*>(&isMakeup), sizeof(bool));
}

ostream& operator<<(ostream& os, const LabSession& session) {
    const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    os << session.sessionId << "|" << session.sectionId << "|" << session.date 
       << "|" << days[session.dayOfWeek] << "|" << session.timing 
       << "|" << (session.isMakeup ? "Yes" : "No");
    return os;
}
