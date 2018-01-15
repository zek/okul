#pragma once

#include <iostream>
#include <string>

using namespace std;

class PersonI {
public:
    virtual void IntroduceYourself() = 0;
};

class Person : public PersonI {
private:
    string name;
public:
    Person(string name) {
        this->name = name;
    }

    void IntroduceYourself() {
        cout << "My name is: " << name << endl;
    }
};

class Decorator : public PersonI {
protected:
    PersonI *person;
public:
    void IntroduceYourself() {
        person->IntroduceYourself();
    }

    Decorator(PersonI *person) {
        this->person = person;
    }
};

class Age : public Decorator {
private:
    int age;
public:
    Age(int age, PersonI *person) : Decorator(person) {
        this->age = age;
    }

    void IntroduceYourself() {
        Decorator::IntroduceYourself();
        cout << "I am " << age << " years old." << endl;
    }
};

class Profession : public Decorator {
private:
    string profession;
public:
    Profession(string profession, PersonI *person) : Decorator(person) {
        this->profession = profession;
    }

    void IntroduceYourself() {
        Decorator::IntroduceYourself();
        cout << "I work as " << profession << "." << endl;
    }
};

class Skill : public Decorator {
private:
    string skill;
public:
    Skill(string skill, PersonI *person) : Decorator(person) {
        this->skill = skill;
    }

    void IntroduceYourself() {
        Decorator::IntroduceYourself();
        cout << "I can " << skill << "." << endl;
    }
};

