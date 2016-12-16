// FILE: pqtest.cpp
// An interactive test program for the new List ADT.
#include <cctype>     // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS and size_t
#include "pqueue1.h"  // With Item defined as int
using namespace std;

// PROTOTYPES for functions used by this test program:
void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// The next character has been read (skipping blanks and newline characters), 
// and this character has been returned.

int get_number(const char message[ ]);
// Postcondition: The user has been prompted to enter an integer. The
// number has been read, echoed to the screen, and returned by the function.


int main( )
{
    PriorityQueue test;    // A PriorityQueue that we'll perform tests on
    char choice;           // A command character entered by the user
    
    cout << "I have initialized an empty Priority Queue." << endl;
    cout << "The data entered into this Priority Queue will be integers,\n";
    cout << "and each item also has an unsigned int for its priority." << endl;

    do
    {
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'E': if (test.is_empty( ))
		          cout << "The Priority Queue is empty." << endl;
                      else
			  cout << "The Priority Queue is not empty." << endl;
	              break;
            case 'G': if (!test.is_empty( ))
                           cout << "Front item is: " << test.get_front( ) << endl;
                      else
                         cout << "There is no current item." << endl;
                      break;
            case 'I': test.insert(
                          get_number("Please enter the next item: "),
                          (unsigned int) get_number("The item's priority: ")
                      );
                      break;
            case 'S': cout << "The size is " << test.size( ) << endl;
                      break;
            case 'Q': cout << "Ridicule is the best test of truth." << endl;
                      break;
            default:  cout << choice << " is invalid. Sorry." << endl;
        }
    }
    while ((choice != 'Q'));

    return EXIT_SUCCESS;
}

void print_menu( )
// Library facilities used: iostream.h
{
    cout << endl; // Print blank line before the menu
    cout << "The following choices are available: " << endl;
    cout << " E   Print the result from the is_empty( ) function" << endl;
    cout << " G   Print the result from the get_front( ) function" << endl;
    cout << " I   Insert a new item with the insert(...) function" << endl;
    cout << " S   Print the result from the size( ) function" << endl;
    cout << " Q   Quit this test program" << endl;
}

char get_user_command( )
// Library facilities used: iostream.h
{
    char command;

    cout << "Enter choice: ";
    cin >> command; // Input of characters skips blanks and newline character

    return command;
}

int get_number(const char message[ ])
// Library facilities used: iostream.h
{
    int result;
    
    cout << message << endl;
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}