#ifndef STUDENT_H
#define STUDENT_H


#include <string> /// string
#include <sstream> /// ostringstream
#include <iostream> // cin, cout
#include <iomanip> /// setprecision
#include "Exception.h"
#include "Advisor.h"

using namespace std;


class Student {
private:
    string firstName;
    string lastName;
    int studentId;
    int year;
    double GPA;
    Advisor *advisor;
    int advisor_id;
    bool assignedFlag = false;

public:

    static Student createStudent(string firstName, string lastName, int studentId, int year, double GPA) {
        Student student;
        student.setFirstName(firstName);
        student.setLastName(lastName);
        student.setStudentId(studentId);
        student.setYear(year);
        student.setGPA(GPA);
        return student;
    }

    friend istream &operator>>(istream &is, Student &s) {
        is >> s.firstName;
        is >> s.lastName;
        is >> s.studentId;
        is >> s.year;
        is >> s.GPA;
        is >> s.advisor_id;
        is >> s.assignedFlag;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Student &s) {
        os << s.firstName << endl;
        os << s.lastName << endl;
        os << s.studentId << endl;
        os << s.year << endl;
        os << s.GPA << endl;
        os << s.advisor_id << endl;
        os << s.assignedFlag << endl;
        return os;
    }
    
    void showStudentDetails();

    bool isSuccessful();

    void currentStatus();


    const string &getFirstName() const {
        return firstName;
    }

    void setFirstName(const string &firstName) {
        Student::firstName = firstName;
    }

    const string &getLastName() const {
        return lastName;
    }

    void setLastName(const string &lastName) {
        Student::lastName = lastName;
    }

    int getStudentId() const {
        return studentId;
    }

    void setStudentId(int studentId) {
        Student::studentId = studentId;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year);

    double getGPA() const {
        return GPA;
    }

    void setGPA(double GPA);

    const Advisor &getAdvisor() const {
        return *advisor;
    }

    void setAdvisor(Advisor &advisor) {
        Student::advisor = &advisor;
    }

    bool isAssignedFlag() const {
        return assignedFlag;
    }

    void setAssignedFlag(bool assignedFlag) {
        Student::assignedFlag = assignedFlag;
    }

};

#endif