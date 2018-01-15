#pragma once

// **************************************************
// ******** This file should not be modified ********
// **************************************************

#include<vector>

using namespace std;


class People {
public:
    People() : m_size(0) {}

    void addPerson(int age, float height) {
        m_size++;
        m_age.push_back(age);
        m_height.push_back(height);
    }

    int age(const int index) const { return m_age[index]; }

    float height(const int index) const { return m_height[index]; }

    size_t size() const { return m_size; }

private:
    std::vector<int> m_age;
    std::vector<float> m_height;
    size_t m_size;
};


class Iterator {
public:
    virtual void next() = 0;

    virtual int object() = 0;

    virtual bool isDone() = 0;

    virtual size_t index() = 0;
};

class DivByIterator : public Iterator {
public:
    DivByIterator(Iterator *iterator, int divBy) {
        m_iterator = iterator;
        m_divBy = divBy;
    }

    bool isDone() {
        return m_iterator->isDone();
    }

    void next() {
        m_iterator->next();
        while (!m_iterator->isDone()) {
            if (m_iterator->object() % m_divBy == 0)
                return;
            m_iterator->next();
        }
    }

    size_t index() {
        return m_iterator->index();
    }

    int object() {
        return m_iterator->object();
    }

private:
    Iterator *m_iterator;
    int m_divBy;
};

class VectorIterator : public Iterator {
public:
    VectorIterator(vector<int> &vector) : m_vector(&vector) {
        m_index = 0;
    }

    int object() {
        return m_vector->at(m_index);
    }

    void next() {
        m_index++;
    }

    bool isDone() {
        return m_index >= m_vector->size();
    }

    size_t index() {
        return m_index;
    }

private:
    vector<int> *m_vector;
    size_t m_index;
};

class PairIterator : public Iterator {
public:
    PairIterator(list <pair<string, int>> &list) {
        m_list = &list;
        it = m_list->begin();
    }

    int object() {
        return (*it).second;
    }

    void next() {
        m_index++;
        it++;
    }

    bool isDone() {
        return it == m_list->end();
    }

    size_t index() {
        return m_index;
    }

private:
    list<pair < string, int >>::
    iterator it;
    list <pair<string, int>> *m_list;
    size_t m_index;
};

class PeopleIterator : public Iterator {
public:
    PeopleIterator(People &people) {
        this->m_people = &people;
        m_index = 0;
    }

    int object() {
        return m_people->age(m_index);
    }

    void next() {
        m_index++;
    }

    bool isDone() {
        return m_index >= m_people->size();
    }

    size_t index() {
        return m_index;
    }

private:
    People *m_people;
    size_t m_index;
};


void Print(Iterator *iter) {
    while (!iter->isDone()) {
        cout << iter->object() << " ";
        iter->next();
    }
    cout << "\n";
}

void PrintSum(Iterator *iter) {
    int sum = 0;
    while (!iter->isDone()) {
        sum += iter->object();
        iter->next();
    }
    cout << "sum: " << sum << "\n";
}

void PrintMaxMin(Iterator *iter, bool index = false) {
    int min, max;
    int iMin, iMax;
    min = max = iter->object();
    iMin = iMax = iter->index();
    iter->next();
    while (!iter->isDone()) {
        if (iter->object() > max) {
            max = iter->object();
            iMax = iter->index();
        }
        if (iter->object() < min) {
            min = iter->object();
            iMin = iter->index();
        }
        iter->next();
    }
    if (index)
        cout << "i_min=" << iMin << "\ti_max=" << iMax << "\n";
    else
        cout << "min=" << min << "\tmax=" << max << "\n";

}