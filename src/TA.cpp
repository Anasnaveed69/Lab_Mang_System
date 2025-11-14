#include "../include/TA.h"

TA::TA() : taId(""), name(""), email(""), studentId("") {}

TA::TA(const string& id, const string& n, const string& e, const string& sid)
    : taId(id), name(n), email(e), studentId(sid) {}

string TA::getTaId() const {
    return taId;
}

string TA::getName() const {
    return name;
}

string TA::getEmail() const {
    return email;
}

string TA::getStudentId() const {
    return studentId;
}

void TA::setTaId(const string& id) {
    taId = id;
}

void TA::setName(const string& n) {
    name = n;
}

void TA::setEmail(const string& e) {
    email = e;
}

void TA::setStudentId(const string& sid) {
    studentId = sid;
}

void TA::serialize(ofstream& out) const {
    size_t len = taId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(taId.c_str(), len);
    len = name.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(name.c_str(), len);
    len = email.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(email.c_str(), len);
    len = studentId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(studentId.c_str(), len);
}

void TA::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    taId.resize(len);
    in.read(&taId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    email.resize(len);
    in.read(&email[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    studentId.resize(len);
    in.read(&studentId[0], len);
}

ostream& operator<<(ostream& os, const TA& ta) {
    os << ta.taId << "|" << ta.name << "|" << ta.email << "|" << ta.studentId;
    return os;
}
