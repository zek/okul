#pragma once

#include"Dish.h"

#include<list>

class Meal
{
public:
  ~Meal () {
    for (Dish* theDish : m_dishes)
      delete theDish;
  }

  const std::list<Dish*>& Dishes () const {return m_dishes;}
  
  int NumberOfDishes () const {return m_dishes.size();}

  void BiteEachDish (const float bitePercent) {
    for (Dish* theDish : m_dishes)
      theDish->Bite(bitePercent);
  }

  void AddDish (Dish* theDish) {
    m_dishes.push_back(theDish);
  }

protected:
  std::list<Dish*> m_dishes;
};
