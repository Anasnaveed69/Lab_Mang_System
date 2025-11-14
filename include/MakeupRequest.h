#ifndef MAKEUPREQUEST_H
#define MAKEUPREQUEST_H

#include <string>
#include "LabSession.h"
#include <iostream>
#include <fstream>
using namespace std;

class MakeupRequest {
private:
    string requestId;
    string sectionId;
    string instructorId;
    Date requestedDate;
    string reason;
    bool approved;
    Date makeupDate;
    bool makeupDateSet;

public:
    MakeupRequest();
    MakeupRequest(const string& id, const string& secId, 
                  const string& instId, const Date& reqDate, const string& r);
    string getRequestId() const;
    string getSectionId() const;
    string getInstructorId() const;
    Date getRequestedDate() const;
    string getReason() const;
    bool isApproved() const;
    Date getMakeupDate() const;
    bool isMakeupDateSet() const;
    void setRequestId(const string& id);
    void setSectionId(const string& secId);
    void setInstructorId(const string& instId);
    void setRequestedDate(const Date& d);
    void setReason(const string& r);
    void setApproved(bool app);
    void setMakeupDate(const Date& d);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const MakeupRequest& request);
};

#endif
