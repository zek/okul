// Please implement missing code to make program produce output shown
// at the bottom of the file.

#include"Functions.h"
#include"MenuItem.h"
#include"Dish.h"

#include<iostream>

int main ()
{
  using namespace std;

  cout<<"===== MENU =====\n";
  MenuItem* porrigeItem = CreateMenuItem("Porrige.txt");
  porrigeItem->Print();

  cout<<"===== Dish =====\n";
  Dish* porrige = CreateDish("Porrige.txt");
  porrige->Print();

  cout<<"*** After first bite ***\n";
  porrige->Bite(5);
  porrige->Print();

  delete porrigeItem;
  delete porrige;

  return 0;
}

/* output
===== MENU =====
Porrige12.320.32milk,wheat,honey 
===== Dish =====
PorrigeEngland1001223Mix milk with wheat and boil.
milk,wheat,honey 
*** After first bite ***
PorrigeEngland951223Mix milk with wheat and boil.
milk,wheat,honey 
*/
