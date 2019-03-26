#include "Student.h"
#include "Advisor.h"


void Student::setGPA(double GPA) {
    if (GPA < 0 || GPA > 4) {
        std::ostringstream str;
        str << "Wrong GPA value for student: " << GPA;
        throw Exception(str.str());
    }
    Student::GPA = GPA;
}

void Student::setYear(int year) {
    if (year < 1 || year > 4) {
        std::ostringstream str;
        str << "Wrong year value for student: " << year;
        throw Exception(str.str());
    }
    Student::year = year;
}

void Student::showStudentDetails() {
    cout << "**************************************" << endl;
    cout << "STUDENT NAME: " << firstName << endl;
    cout << "STUDENT LASTNAME: " << lastName << endl;
    cout << "STUDENT ID: " << studentId << endl;
    cout << "YEAR: " << year << endl;
    cout << "GPA: " << setprecision(2) << GPA << endl;
    if(advisor){
        cout << "ADVISOR: " << advisor->getFirstName() << " " << advisor->getLastName() << endl;
    }
    cout << "**************************************" << endl;
}

bool Student::isSuccessful() {
    return GPA >= 2.5;
}

void Student::currentStatus() {
    cout << "**********************************" << endl;
    cout << "STUDENT: " << firstName << " " << lastName;
    if (isSuccessful()) {
        cout << "SUCCESSFUL" << endl;
    } else {
        cout << "NOT SUCCESSFUL" << endl;
    }
    cout << "**********************************" << endl;
}
