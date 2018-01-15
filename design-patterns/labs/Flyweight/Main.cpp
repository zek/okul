// The code can be compiled using provided makefile. Please, compile
// the program and execute it.

// The program reads dictionaries that are saved in text files and
// prints words with given indecies.

// Please, run the program and check what is the execution time. If it
// is less than 10 seconds, please increase number of words that are
// printed by changing value of variable size.

// Profiling of the program execution can be done with command:
// make prof
// The most interesting is the second column from left in the last
// line, because it shows total acumulated time of program execution.

// Please refactor the Dictionary class using flyweight design pattern
// so that the program is optimised and execution is significantly
// faster. Please, use output from profiling, described above, to
// compare execution times. The file Main.cpp should not be changed
// i.e. from client's point of view no change should be visible.

// Please, remember that refactoring of the code may require adjusting
// Makefile.

#include"Dictionary.h"

#include<iostream>
#include<string>
#include<vector>

void Print (const std::vector<Dictionary>& dictVector) {
  for (const Dictionary& dict : dictVector)
    std::cout<<dict.Word()<<" ";
  std::cout<<"\n";
}

int main ()
{
  using namespace std;

  const int size = 10;

  cout<<"=== POLISH ===\n";
  vector<Dictionary> polish;
  for (int i = 0; i < size; ++i)
    polish.push_back (Dictionary("slowa.txt", i*10000));

  Print (polish);


  cout<<"\n=== ENGLISH ===\n";
  vector<Dictionary> english;
  for (int i = 0; i < size; ++i)
    english.push_back (Dictionary("american-english", i*10000));

  Print(english);

  cout<<"\n=== POLISH 2 ===\n";
  for (int i = 0; i < size; ++i)
    polish[i].SetIndex (polish[i].Index() + (i*10000));

  Print(polish);

  return 0;
}
