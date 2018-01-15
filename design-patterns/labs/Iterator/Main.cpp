// The code can be compiled using provided makefile. Please, compile
// the program and execute it.

// The program operates on 3 containers and runs requests on integers
// stored in them.

// Please, refactor the main function using iterator design pattern in
// order to reduce code duplication.

// Please, remember that refactoring of the code may require adjusting
// Makefile.


#include<iostream>
#include<cstdlib>
#include<string>
#include<list>
#include<utility>
#include<vector>

#include"People.h"

int main ()
{
  using namespace std;

  // ********** initialise containers **********
  srand(1);

  vector<int> numbers (15);
  for (int& num : numbers)
    num = rand()%1000;

  list<pair<string, int > > pairs (20);
  for (pair<string, int>& element : pairs) {
    element.second = rand()%100;
    for (int i = 0; i < 5; ++i)
      element.first += (rand()%25 + 97);
  }

  People listOfPeople;
  for (int i = 0; i < 12; ++i)
    listOfPeople.addPerson(rand()%100, rand()%100 + 100 + ((float)(rand()%100)/100));


  // ********** OPERATE **********

  std::cout<<"===== PRINT =====\n";
  Print(new VectorIterator(numbers));
  Print(new PairIterator(pairs));
  Print(new PeopleIterator(listOfPeople));

  std::cout<<"===== PRINT DIVISIBLE BY 3 =====\n";
  Print(new DivByIterator(new VectorIterator(numbers), 3));
  Print(new DivByIterator(new PairIterator(pairs), 3));
  Print(new DivByIterator(new PeopleIterator(listOfPeople), 3));

  std::cout<<"===== SUM =====\n";
  PrintSum(new VectorIterator(numbers));
  PrintSum(new PairIterator(pairs));
  PrintSum(new PeopleIterator(listOfPeople));


  std::cout<<"===== SUM DIVISBLE BY 3 =====\n";
  PrintSum(new DivByIterator(new VectorIterator(numbers), 3));
  PrintSum(new DivByIterator(new PairIterator(pairs), 3));
  PrintSum(new DivByIterator(new PeopleIterator(listOfPeople), 3));

  std::cout<<"===== MAXIMUM AND MINIMUM =====\n";
  PrintMaxMin(new VectorIterator(numbers));
  PrintMaxMin(new PairIterator(pairs));
  PrintMaxMin(new PeopleIterator(listOfPeople));

  std::cout<<"===== MAXIMUM AND MINIMUM DIVISIBLE BY 3 =====\n";
  PrintMaxMin(new DivByIterator(new VectorIterator(numbers), 3));
  PrintMaxMin(new DivByIterator(new PairIterator(pairs), 3));
  PrintMaxMin(new DivByIterator(new PeopleIterator(listOfPeople), 3));

  std::cout<<"===== INDEX MIN AND MAX =====\n";
  PrintMaxMin(new VectorIterator(numbers), true);
  PrintMaxMin(new PairIterator(pairs), true);
  PrintMaxMin(new PeopleIterator(listOfPeople), true);

  std::cout<<"===== INDEX MIN AND MAX DIVISIBLE BY 3 =====\n";
  PrintMaxMin(new DivByIterator(new VectorIterator(numbers), 3), true);
  PrintMaxMin(new DivByIterator(new PairIterator(pairs), 3), true);
  PrintMaxMin(new DivByIterator(new PeopleIterator(listOfPeople), 3), true);


  return 0;
}
