
#include"Functions.h"
#include"Order.h"
#include"Meal.h"

#include<iostream>
#include<list>

int main ()
{
  using namespace std;

  Singleton* app = Singleton::Instance();

  cout<<"===== BIG ORDER =====\n";
  Order* bigOrder = app->CreateBigOrder();


  bigOrder->Print();
  cout<<"\n";
  cout<<"Total price: "<<bigOrder->TotalPrice()<<"\n";
  cout<<"Total tax: "<<bigOrder->TotalTax()<<"\n";
  cout<<"\n";

  cout<<"===== BIG MEAL =====\n";
  Meal* bigMeal = app->CreateBigMeal();

  cout<<"Number of dishes: "<<bigMeal->NumberOfDishes()<<"\n";
  const list<Dish*>& dishes = bigMeal->Dishes();

  cout<<"*** First print of dishes ***\n";
  for (const Dish* oneDish : dishes)
    cout<<oneDish->Name()<<"\t"<<oneDish->Callories()<<"\t"<<oneDish->PercentLeft()<<"\n";
  cout<<"\n";

  const double bitePercent = 5;
  bigMeal->BiteEachDish(bitePercent);

  cout<<"*** After first bite ***\n";
  for (const Dish* oneDish : dishes)
    cout<<oneDish->Name()<<"\t"<<oneDish->Callories()<<"\t"<<oneDish->PercentLeft()<<"\n";
  cout<<"\n";

  Dish* firstDish = dishes.front();
  firstDish->Bite(10);

  cout<<"*** Bite only one ***\n";
  for (const Dish* oneDish : dishes)
    cout<<oneDish->Name()<<"\t"<<oneDish->Callories()<<"\t"<<oneDish->PercentLeft()<<"\n";


  delete bigOrder;
  delete bigMeal;

  return 0;
}

