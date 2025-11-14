#include "../include/MakeupRequest.h"

MakeupRequest::MakeupRequest() : requestId(""), sectionId(""), instructorId(""), 
                                  requestedDate(), reason(""), approved(false), 
                                  makeupDate(), makeupDateSet(false) {}

MakeupRequest::MakeupRequest(const string& id, const string& secId,
                             const string& instId, const Date& reqDate, const string& r)
    : requestId(id), sectionId(secId), instructorId(instId), requestedDate(reqDate),
      reason(r), approved(false), makeupDate(), makeupDateSet(false) {}

string MakeupRequest::getRequestId() const {
    return requestId;
}

string MakeupRequest::getSectionId() const {
    return sectionId;
}

string MakeupRequest::getInstructorId() const {
    return instructorId;
}

Date MakeupRequest::getRequestedDate() const {
    return requestedDate;
}

string MakeupRequest::getReason() const {
    return reason;
}

bool MakeupRequest::isApproved() const {
    return approved;
}

Date MakeupRequest::getMakeupDate() const {
    return makeupDate;
}

bool MakeupRequest::isMakeupDateSet() const {
    return makeupDateSet;
}

void MakeupRequest::setRequestId(const string& id) {
    requestId = id;
}

void MakeupRequest::setSectionId(const string& secId) {
    sectionId = secId;
}

void MakeupRequest::setInstructorId(const string& instId) {
    instructorId = instId;
}

void MakeupRequest::setRequestedDate(const Date& d) {
    requestedDate = d;
}

void MakeupRequest::setReason(const string& r) {
    reason = r;
}

void MakeupRequest::setApproved(bool app) {
    approved = app;
}

void MakeupRequest::setMakeupDate(const Date& d) {
    makeupDate = d;
    makeupDateSet = true;
}

void MakeupRequest::serialize(ofstream& out) const {
    size_t len = requestId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(requestId.c_str(), len);
    len = sectionId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(sectionId.c_str(), len);
    len = instructorId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(instructorId.c_str(), len);
    out.write(reinterpret_cast<const char*>(&requestedDate.year), sizeof(int));
    out.write(reinterpret_cast<const char*>(&requestedDate.month), sizeof(int));
    out.write(reinterpret_cast<const char*>(&requestedDate.day), sizeof(int));
    len = reason.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(reason.c_str(), len);
    out.write(reinterpret_cast<const char*>(&approved), sizeof(bool));
    out.write(reinterpret_cast<const char*>(&makeupDate.year), sizeof(int));
    out.write(reinterpret_cast<const char*>(&makeupDate.month), sizeof(int));
    out.write(reinterpret_cast<const char*>(&makeupDate.day), sizeof(int));
    out.write(reinterpret_cast<const char*>(&makeupDateSet), sizeof(bool));
}

void MakeupRequest::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    requestId.resize(len);
    in.read(&requestId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    sectionId.resize(len);
    in.read(&sectionId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    instructorId.resize(len);
    in.read(&instructorId[0], len);
    in.read(reinterpret_cast<char*>(&requestedDate.year), sizeof(int));
    in.read(reinterpret_cast<char*>(&requestedDate.month), sizeof(int));
    in.read(reinterpret_cast<char*>(&requestedDate.day), sizeof(int));
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    reason.resize(len);
    in.read(&reason[0], len);
    in.read(reinterpret_cast<char*>(&approved), sizeof(bool));
    in.read(reinterpret_cast<char*>(&makeupDate.year), sizeof(int));
    in.read(reinterpret_cast<char*>(&makeupDate.month), sizeof(int));
    in.read(reinterpret_cast<char*>(&makeupDate.day), sizeof(int));
    in.read(reinterpret_cast<char*>(&makeupDateSet), sizeof(bool));
}

ostream& operator<<(ostream& os, const MakeupRequest& request) {
    os << request.requestId << "|" << request.sectionId << "|" << request.instructorId 
       << "|" << request.requestedDate << "|" << request.reason 
       << "|" << (request.approved ? "Yes" : "No");
    if (request.makeupDateSet) {
        os << "|" << request.makeupDate;
    }
    return os;
}
