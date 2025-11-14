#include "../include/Instructor.h"

Instructor::Instructor() : instructorId(""), name(""), email(""), department("") {}

Instructor::Instructor(const string& id, const string& n, const string& e, const string& dept)
    : instructorId(id), name(n), email(e), department(dept) {}

string Instructor::getInstructorId() const {
    return instructorId;
}

string Instructor::getName() const {
    return name;
}

string Instructor::getEmail() const {
    return email;
}

string Instructor::getDepartment() const {
    return department;
}

void Instructor::setInstructorId(const string& id) {
    instructorId = id;
}

void Instructor::setName(const string& n) {
    name = n;
}

void Instructor::setEmail(const string& e) {
    email = e;
}

void Instructor::setDepartment(const string& dept) {
    department = dept;
}

void Instructor::serialize(ofstream& out) const {
    size_t len = instructorId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(instructorId.c_str(), len);
    len = name.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(name.c_str(), len);
    len = email.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(email.c_str(), len);
    len = department.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(department.c_str(), len);
}

void Instructor::deserialize(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    instructorId.resize(len);
    in.read(&instructorId[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    email.resize(len);
    in.read(&email[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    department.resize(len);
    in.read(&department[0], len);
}

ostream& operator<<(ostream& os, const Instructor& instructor) {
    os << instructor.instructorId << "|" << instructor.name << "|" << instructor.email << "|" << instructor.department;
    return os;
}
