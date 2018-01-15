#pragma once

#include<iostream>
#include<vector>

using namespace std;

class Arithmetic {
public:
    virtual void PrintFormula() = 0;

    virtual float GetValue() = 0;

    void PrintValue() {
        cout << GetValue();
    };

    void PrintAll() {
        PrintFormula();
        cout << " = ";
        PrintValue();
    }

};

class MathNum : public Arithmetic {
private:
    double number;
public:
    MathNum(double n) {
        this->number = n;
    }

    void PrintFormula() {
        cout << number;
    }

    float GetValue() {
        return number;
    }

    void Set(float number) {
        this->number = number;
    }
};

class Sum : public Arithmetic {
private:
    vector<Arithmetic *> list;
public:

    Sum(void) {
        this->list = vector<Arithmetic *>();
    }


    Sum(vector<Arithmetic *> list) {
        this->list = list;
    }


    Sum &operator<<(Arithmetic &temp) {
        list.push_back(&temp);
        return *this;
    }

    void PrintFormula() {
        cout << "(";
        std::vector<Arithmetic *>::iterator it = list.begin();
        while (it != list.end()) {
            (*it)->PrintFormula();
            ++it;
            if (it != list.end()) {
                cout << " + ";
            }
        }
        cout << ")";
    }

    float GetValue() {
        float sum = 0;
        for (std::vector<Arithmetic *>::iterator it = list.begin(); it != list.end(); ++it) {
            sum += (*it)->GetValue();
        }
        return sum;
    }
};


class Multiply : public Arithmetic {
private:
    vector<Arithmetic *> list;
public:

    Multiply(void) {
        this->list = vector<Arithmetic *>();
    }


    Multiply(vector<Arithmetic *> list) {
        this->list = list;
    }


    Multiply &operator<<(Arithmetic &temp) {
        list.push_back(&temp);
        return *this;
    }

    void PrintFormula() {
        cout << "(";
        std::vector<Arithmetic *>::iterator it = list.begin();
        while (it != list.end()) {
            (*it)->PrintFormula();
            ++it;
            if (it != list.end()) {
                cout << " * ";
            }
        }
        cout << ")";
    }

    float GetValue() {
        if (list.empty()) {
            return 0;
        }
        float sum = 1;
        for (std::vector<Arithmetic *>::iterator it = list.begin(); it != list.end(); ++it) {
            sum *= (*it)->GetValue();
        }
        return sum;
    }
};

class Difference : public Arithmetic {
private:
    vector<Arithmetic *> list;
public:

    Difference(Arithmetic &first) {
        this->list = vector<Arithmetic *>();

        this->list.push_back(&first);

    }

    Difference &operator<<(Arithmetic &temp) {
        list.push_back(&temp);
        return *this;
    }

    void PrintFormula() {
        cout << "(";
        std::vector<Arithmetic *>::iterator it = list.begin();
        while (it != list.end()) {
            (*it)->PrintFormula();
            ++it;
            if (it != list.end()) {
                cout << " - ";
            }
        }
        cout << ")";
    }

    float GetValue() {
        std::vector<Arithmetic *>::iterator it = list.begin();
        float sum;
        if (it != list.end()) {
            sum = (*it)->GetValue();
        } else {
            sum = 0;
        }
        ++it;
        while (it != list.end()) {
            sum -= (*it)->GetValue();
            ++it;
        }
        return sum;
    }
};