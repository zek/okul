#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H


#include "Student.h"
#include <string.h>
#include <fstream>

class Assignment {
public:
    void assignStudentToAdvisor(Advisor advisor, Student student) {
        int nosa = advisor.getNumberOfStudentsAssigned();
        if (nosa < advisor.getAllowedStudentCount()) {
            advisor.setNumberOfStudentsAssigned(nosa + 1);
            student.setAdvisor(advisor);
        } else {
            std::ostringstream str;
            str << "Cannot assign more students to advisor ADVISOR ID: " << advisor.getAdvisorId();
            throw Exception(str.str());
        }
    }

    Student recordStudent(string firstName, string lastName, int studentId, int year, double GPA) {
        Student student = Student::createStudent(firstName, lastName, studentId, year, GPA);

        //std::ostringstream str;
        //str << "student_" << studentId << ".data";
        ofstream out("student.data");
        out << student;
        out.close();

        return student;
    }

    Advisor recordAdvisor(string firstName, string lastName, int advisorId) {
        Advisor advisor = Advisor::createAdvisor(firstName, lastName, advisorId);

        //std::ostringstream str;
        //str << "advisor_" << advisorId << ".data";
        ofstream out("advisor.data");
        out << advisor;
        out.close();

        return advisor;
    }

    void main() {
        Student student1 = Student::createStudent("Ali", "Sunal", 1000, 1, 3.5);
        Student student2 = Student::createStudent("Mehmet", "Fidan", 1001, 1, 3.5);
        Student student3 = Student::createStudent("Hakan", "Tan", 1002, 1, 3.5);
        Student student4 = Student::createStudent("Nihat", "Kaya", 1003, 1, 3.5);

        Advisor advisor1 = Advisor::createAdvisor("Gizem", "Duran", 101);
        Advisor advisor2 = Advisor::createAdvisor("Nuri", "Ketenci", 101);
        Advisor advisor3 = Advisor::createAdvisor("Mithat", "Sakar", 101);

        student1.showStudentDetails();
        student2.showStudentDetails();
        student3.showStudentDetails();
        student4.showStudentDetails();

        advisor1.showAdvisorDetails();
        advisor2.showAdvisorDetails();
        advisor3.showAdvisorDetails();

        assignStudentToAdvisor(advisor1, student1);
        assignStudentToAdvisor(advisor1, student2);
        assignStudentToAdvisor(advisor2, student3);
        assignStudentToAdvisor(advisor3, student4);

        try {
            Student student5 = Student::createStudent("Mulayim", "Kaya", 1003, 1, 3.5);
            Student student6 = Student::createStudent("Miray", "Kaya", 1003, 1, 3.5);
            assignStudentToAdvisor(advisor1, student5);
            assignStudentToAdvisor(advisor1, student6);
        } catch (Exception exc) {
            cout << exc.what() << endl;
        }

        try {
            Student::createStudent("Mulayim", "Kaya", 1003, 1, 5.5);
        } catch (Exception exc) {
            cout << exc.what() << endl;
        }
        try {
            Student::createStudent("Mulayim", "Kaya", 1003, 1, -5.5);
        } catch (Exception exc) {
            cout << exc.what() << endl;
        }
        try {
            Student::createStudent("Mulayim", "Kaya", 1003, 5, 4);
        } catch (Exception exc) {
            cout << exc.what() << endl;
        }

        advisor1.showAdvisorDetails();
        student1.currentStatus();


    }

};


#endif