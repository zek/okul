#pragma once

#include "Builder.h"

class Director {
private:
    Builder *builder;
public:
    Director(Builder *_builder) {
        builder = _builder;
    }

    void construct() {
        builder->create();
        builder->addRecord("Dumplings", 12.3, 2.22, 1234);
        builder->addRecord("Pasta", 32.8, 6.66, 981);
        builder->addRecord("Pierogi", 22.2, 1.33, 1111);
        builder->addRecord("Gazpacho", 56.99, 8.99, 15);
        builder->addRecord("Chicken", 30.99, 1.66, 1042);
    }

};
