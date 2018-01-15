#pragma once

#include <string>

class Builder {
public:
    virtual void create() = 0;

    virtual void addRecord(const std::string name, const float price, const float tax, const float callories) = 0;

    //virtual void *get() = 0;
};
