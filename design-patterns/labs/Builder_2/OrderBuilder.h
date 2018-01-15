#pragma once

#include "Builder.h"
#include "Record.h"
#include "Order.h"

class OrderBuilder : public Builder{
private:
    Order* order;
    
public:

    void create(){
        order = new Order;
    }

    void addRecord(const std::string name, const float price, const float tax, const float callories){
        Record* record = new Record(name, price, tax);
        order->AddRecord(record);
    }
    
    Order* getOrder(){
        return order;
    }
};
