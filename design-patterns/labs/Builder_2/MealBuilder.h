#pragma once

#include "Builder.h"
#include "Record.h"
#include "Meal.h"

class MealBuilder : public Builder{
private:
    Meal* meal;
    
public:

    void create(){
        meal = new Meal;
    }

    void addRecord(const std::string name, const float price, const float tax, const float callories){
        Dish* dish = new Dish(name, callories);
        meal->AddDish(dish);
    }
    
    Meal* getMeal(){
        return meal;
    }
};
