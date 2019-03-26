#ifndef ADVISOR_H
#define ADVISOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


class Advisor {
private:
    string firstName;
    string lastName;
    int advisorId;
    int numberOfStudentsAssigned;
    int allowedStudentCount; // max 3

public:
    static Advisor createAdvisor(string firstName, string lastName, int advisorId) {
        Advisor advisor;
        advisor.setFirstName(firstName);
        advisor.setLastName(lastName);
        advisor.setAdvisorId(advisorId);
        advisor.setAllowedStudentCount(3);
        advisor.numberOfStudentsAssigned = 0;
        return advisor;
    }


    friend istream &operator>>(istream &is, Advisor &s) {
        is >> s.firstName;
        is >> s.lastName;
        is >> s.advisorId;
        is >> s.numberOfStudentsAssigned;
        is >> s.allowedStudentCount;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Advisor &s) {
        os << s.firstName << endl;
        os << s.lastName << endl;
        os << s.advisorId << endl;
        os << s.numberOfStudentsAssigned << endl;
        os << s.allowedStudentCount << endl;
        return os;
    }

    const string &getFirstName() const {
        return firstName;
    }

    void setFirstName(const string &firstName) {
        Advisor::firstName = firstName;
    }

    const string &getLastName() const {
        return lastName;
    }

    void setLastName(const string &lastName) {
        Advisor::lastName = lastName;
    }

    int getAdvisorId() const {
        return advisorId;
    }

    void setAdvisorId(int advisorId) {
        Advisor::advisorId = advisorId;
    }

    int getNumberOfStudentsAssigned() const {
        return numberOfStudentsAssigned;
    }

    int getAllowedStudentCount() const {
        return allowedStudentCount;
    }

    void setAllowedStudentCount(unsigned char allowedStudentCount) {
        Advisor::allowedStudentCount = allowedStudentCount;
    }

    void setNumberOfStudentsAssigned(int numberOfStudentsAssigned) {
        Advisor::numberOfStudentsAssigned = numberOfStudentsAssigned;
    }


    void showAdvisorDetails() {
        cout << "**************************************" << endl;
        cout << "ADVISOR NAME: " << firstName << endl;
        cout << "ADVISOR LASTNAME: " << lastName << endl;
        cout << "ADVISOR ID: " << advisorId << endl;
        cout << "STUDENTS ASSIGNED: " << numberOfStudentsAssigned << endl;
        cout << "ALLOWED STUDENTS: " << allowedStudentCount << endl;
        cout << "**************************************" << endl;
    }

};


#endif