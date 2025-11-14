#ifndef TA_H
#define TA_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class TA {
private:
    string taId;
    string name;
    string email;
    string studentId;

public:
    TA();
    TA(const string& id, const string& n, const string& e, const string& sid);
    string getTaId() const;
    string getName() const;
    string getEmail() const;
    string getStudentId() const;
    void setTaId(const string& id);
    void setName(const string& n);
    void setEmail(const string& e);
    void setStudentId(const string& sid);
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
    friend ostream& operator<<(ostream& os, const TA& ta);
};

#endif
