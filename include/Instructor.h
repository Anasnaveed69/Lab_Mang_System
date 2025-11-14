#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Instructor {
private:
    string instructorId;
    string name;
    string email;
    string department;

public:
    Instructor();
    Instructor(const string& id, const string& n, const string& e, const string& dept);
    string getInstructorId() const;
    string getName() const;
    string getEmail() const;
    string getDepartment() const;
    void setInstructorId(const string& id);
    void setName(const string& n);
    void setEmail(const string& e);
    void setDepartment(const string& dept);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const Instructor& instructor);
};

#endif
