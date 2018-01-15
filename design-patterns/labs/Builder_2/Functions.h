#include "Director.h"
#include "OrderBuilder.h"
#include "MealBuilder.h"
#include "Order.h"
#include "Meal.h"



class Singleton{
public:
    static Singleton* Instance(){
        if(m_instance == nullptr){
            m_instance = new Singleton;
        }
        return m_instance;
    }

    Order *CreateBigOrder() {
        OrderBuilder builder;
        Director director(&builder);
        director.construct();
        Order *order = builder.getOrder();
        return order;
    }

    Meal *CreateBigMeal() {
        MealBuilder builder;
        Director director(&builder);
        director.construct();
        Meal *meal = builder.getMeal();
        return meal;
    }
private:
    Singleton(){}
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;
