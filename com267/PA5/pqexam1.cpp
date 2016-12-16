// FILE: pqexam1.cpp

// DESCRIPTION:
// Each function of this program tests part of the
// PriorityQueue class, returning
// some number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...
//
// WHAT'S NEW:
// This new version of the test program includes an improved test for heap
// leaks by overriding the new and delete operators. Users should consider
// placing these new and delete operators into a separate cpp file, but
// I have included everything in one file for easier distribution.

#include <iostream> // Provides cout.
#include <string.h>   // Provides memcpy.
#include <stdlib.h>   // Provides size_t.
#include "pqueue1.h"  // Provides the PriorityQueue class.

using namespace std;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 4;  
const int POINTS[MANY_TESTS+1] = {
    20,  // Total points for all tests.
    10,  // Test 1 points
     4,  // Test 2 points
     3,  // Test 3 points
     3   // Test 4 points
};
const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for the PriorityQueue class",
    "simple tests of insert and get_front",
    "Testing for possible heap leaks",
    "Testing the copy constructor",
    "Testing the assignment operator"
};

// **************************************************************************
// Replacements for new and delete:
// The next two functions replace the new and delete operators. Any code
// that is linked with this .cxx file will use these replacements instead
// of the standard new and delete. The replacements provide three features:
// 1. The global variable memory_used_now keeps track of how much memory has
//    been allocated by calls to new. (The global variable is static so that
//    it cannot be accessed outside of this .cxx file.)
// 2. The new operator fills all newly allocated memory with a GARBAGE char.
// 3. Each block of newly allocated memory is preceeded and followed by a
//    border of BORDER_SIZE characters. The first part of the front border
//    contains a copy of the size of the allocated memory. The rest of the
//    border contains a BORDER char.
// During any delete operation, the border characters are checked. If any
// border character has been changed from BORDER to something else, then an
// error message is printed and the program is halted. This stops most
// cases of writing beyond the ends of the allocated memory.
// **************************************************************************

const  size_t BORDER_SIZE     = 2*sizeof(double);
const  char   GARBAGE         = 'g';
const  char   BORDER          = 'b';
static size_t memory_used_now = 0;

void* operator new(size_t size)
{
    char   *whole_block;   // Pointer to the entire block that we get from heap
    size_t *size_spot;     // Spot in the block where to store a copy of size
    char   *front_border;  // The border bytes in front of the user's memory 
    char   *middle;        // The memory to be given to the calling program
    char   *back_border;   // The border bytes at the back of the user's memory
    size_t i;              // Loop control variable

    // Allocate the block of memory for the user and for the two borders.
    whole_block = (char *) malloc(2*BORDER_SIZE + size);
    if (whole_block == NULL)
    {
        cout << "Insufficient memory for a call to the new operator." << endl;
        exit(0);
    }

    // Figure out the start points of the various pieces of the block.
    size_spot = (size_t *) whole_block;
    front_border = (char *) (whole_block + sizeof(size_t));
    middle = (char *) (whole_block + BORDER_SIZE);
    back_border = middle + size;

    // Put a copy of the size at the start of the block.
    *size_spot = size;

    // Fill the borders and the middle section.
    for (i = 0; i < BORDER_SIZE - sizeof(size_t); i++)
        front_border[i] = BORDER;
    for (i = 0; i < size; i++)
        middle[i] = GARBAGE;
    for (i = 0; i < BORDER_SIZE; i++)
        back_border[i] = BORDER;

    // Update the global static variable showing how much memory is now used.
    memory_used_now += size;
    
    return middle;
}

void operator delete(void* p)
{
    char   *whole_block;   // Pointer to the entire block that we get from heap
    size_t *size_spot;     // Spot in the block where to store a copy of size
    char   *front_border;  // The border bytes in front of the user's memory 
    char   *middle;        // The memory to be given to the calling program
    char   *back_border;   // The border bytes at the back of the user's memory
    size_t i;              // Loop control variable
    size_t size;           // Size of the block being returned
    bool   corrupt;        // Set to true if the border was corrupted

    // Figure out the start of the pieces of the block, and the size.
    whole_block = ((char *) (p)) - BORDER_SIZE;
    size_spot = (size_t *) whole_block;
    size = *size_spot;
    front_border = (char *) (whole_block + sizeof(size_t));
    middle = (char *) (whole_block + BORDER_SIZE);
    back_border = middle + size;

    // Check the borders for the BORDER character.
    corrupt = false;
    for (i = 0; i < BORDER_SIZE - sizeof(size_t); i++)
        if (front_border[i] != BORDER)
            corrupt = true;
    for (i = 0; i < BORDER_SIZE; i++)
        if (back_border[i] != BORDER)
            corrupt = true;

    if (corrupt)
    {
        cout << "The delete operator has detected that the program wrote\n";
        cout << "beyond the ends of a block of memory that was allocated\n";
        cout << "by the new operator. Program will be halted." << endl;
        exit(0);
    }
    else
    {
        // Fill memory with garbage in case program tries to use it
        // even after the delete.
        for (i = 0; i < size + 2*BORDER_SIZE; i++)
            whole_block[i] = GARBAGE;
        free(whole_block);
        memory_used_now -= size;
    }
    
}


// **************************************************************************
// bool correct(PriorityQueue& test, size_t n, int items[])
// Postcondition: Some tests have been run on the test priority queue.
// If this priority queue has n items, and these items are items[0]
// through items[n-1] (in that order), then the function has printed
// "Test passed." to cout and returned true. Otherwise the function
// has printed "Test failed." to cout and returned false.
// NOTE: If all tests were passed, then the test PriorityQueue has
// also been emptied.
// **************************************************************************
bool correct(PriorityQueue& test, size_t n, int items[])
// Postcondition: Some tests have been run on the test priority queue.
// If this priority queue has n items, and these items are items[0]
// through items[n-1] (in that order), then the function has printed
// "Test passed." to cout and returned true. Otherwise the function
// has printed "Test failed." to cout and returned false.
// NOTE: If all tests were passed, then the test PriorityQueue has
// also been emptied.
{
    size_t i;
    bool answer = true;
    if (test.size( ) != n)
        answer = false;
    else if (test.is_empty( ) != (n == 0))
        answer = false;
    else
        for (i = 0; answer && (i < n); i++)
            if (items[i] != test.get_front( ))
                answer = false;
    cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
    return answer;
}

int test1( )
// Postcondition: A handful of simple tests have been run on the 
// PriorityQueue data type. If all tests are passed, then the function
// returns POINTS[1]. Otherwise the function returns zero.
{
    // A random test will be done with TEST_SIZE elements. Each
    // element will have a priority below PRIORITY_LIMIT.
    const size_t TEST_SIZE = 400;
    const unsigned int PRIORITY_LIMIT = 100;
    
    PriorityQueue test;
    int items[8] = { 100, 200, 3, 4, 5, 6, 8, 7 };
    int occurs[PRIORITY_LIMIT];
    int rand_items[TEST_SIZE];
    char test_letter = 'A';
    int i;
    unsigned int priority;

    cout << test_letter++ << ". ";
    cout << "Testing size and is_empty for an empty priority queue.";
    cout << endl;
    if (!correct(test, 0, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Adding one item to the queue, and then testing\n";
    cout << "   is_empty, size, and get_front.";
    cout << endl;
    test.insert(100, 1);
    if (!correct(test, 1, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (first has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(100, 10);
    test.insert(200, 5);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (second has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(200, 5);
    test.insert(100, 10);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting eight items with priorities of\n";
    cout << "   8, 10, 3, 3, 8, 6, 10, 6 (in that order)\n";
    cout << "   Then checking that all items come out correctly.";
    cout << endl;
    test.insert(3, 8);
    test.insert(100, 10);
    test.insert(8, 3);
    test.insert(7, 3);
    test.insert(4, 8);
    test.insert(5, 6);
    test.insert(200, 10);
    test.insert(6, 6);
    if (!correct(test, 8, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting " << TEST_SIZE << " random items with random\n";
    cout << "   priorities, and checking that all items come out right.";
    cout << endl;
    for (priority = 0; priority < PRIORITY_LIMIT; priority++)
        occurs[priority] = 0;
    for (i = 0; i < TEST_SIZE; i++)
    {
        // Insert a bunch of random items, using items themselves as priorities
        priority = (unsigned) (rand( ) % 100);
        test.insert((int) priority, priority);
        occurs[priority]++;
    }
    priority = PRIORITY_LIMIT-1;
    for (i = 0; i < TEST_SIZE; i++)
    {
        while (occurs[priority] == 0)
            priority--;
        rand_items[i] = (int) priority;
        occurs[priority]--;
    }
    if (!correct(test, TEST_SIZE, rand_items)) return 0;

    return POINTS[1];
}

    
// **************************************************************************
// int test2( )
//   Tries to find a heap leak in the assignment operator or the
//   destructor.
//   Returns POINTS[2] if no leaks are found. Otherwise returns 0.
// **************************************************************************
int test2( )
{
    const size_t TEST_SIZE = 200;
    PriorityQueue test, empty;
    PriorityQueue* pq_ptr;
    size_t base_usage;
    int i;
    int next;

    cout << "Checking for possible heap leak." << endl;
    cout << "This could occur if the assignment operator, get_front, or\n";
    cout << "the destructor does not correctly release memory.\n";

    // Test get_front for a heap leak
    cout << "Testing for heap leak in get_front..." << flush;
    base_usage = memory_used_now;
    for (i = 0; i < TEST_SIZE; i++)
        test.insert(i, unsigned(i));
    for (i = 0; i < TEST_SIZE; i++)
        next = test.get_front( );
    if (memory_used_now != base_usage)
    {
        cout << "\n    Test failed. Probable heap leak in get_front." << endl;
        return 0;
    }
    else
        cout << "passed." << endl;

    // Test for heap leak in destructor.
    cout << "Testing for heap leak in destructor ... " << flush;
    pq_ptr = new PriorityQueue;    
    for (i = 0; i < TEST_SIZE; i++)
        pq_ptr->insert(i, unsigned(i));
    delete pq_ptr;
    if (memory_used_now != base_usage)
    {
        cout << "\n    Test failed. Possible heap leak in copy constructor." << endl;
        return 0;
    }
    else
        cout << "passed." << endl;

    // Test for heap leak in assignment operator.
    cout << "Testing for heap leak in assignment operator ... " << flush;
    for (i = 0; i < TEST_SIZE; i++)
        test.insert(i, unsigned(i));
    test = empty; // Should return test's list to the heap
    if (memory_used_now != base_usage)
    {
        cout << "\n    Test failed. Possible heap leak in assignment operator." << endl;
        return 0;
    }
    else
        cout << "passed." << endl;

    cout << "No heap leaks found." << endl;
    return POINTS[2];
}

int test3( )
// Postcondition: The PriorityQueue's copy constructor has been tested.
// The return value is 10 if the test was passed. Otherwise the return
// value is zero.
{
    PriorityQueue test;
    int items[4] = { 1, 2, 3, 4 };

    cout << "A. Testing that copy constructor works okay for empty queue...";
    cout << flush;
    PriorityQueue copy1(test);
    if (!correct(copy1, 0, items)) return 0;

    cout << "B. Testing copy constructor with 4-item queue...";
    cout << flush;
    test.insert(1, 100);
    test.insert(2, 50);
    test.insert(3, 25);
    test.insert(4, 10);
    PriorityQueue copy2(test);
    test.insert(5, 80); // Alter the original, but not the copy
    if (!correct(copy2, 4, items)) return 0;

    cout << "Copy constructor seems okay." << endl;
    return POINTS[3];
}

int test4( )
// Postcondition: The PriorityQueue's assignment operator has been tested.
// The return value is 10 if the test was passed. Otherwise the return
// value is zero.
{
    PriorityQueue test;
    int items[4] = { 1, 2, 3, 4 };
    char *oldbytes = new char[sizeof(PriorityQueue)];
    char *newbytes = new char[sizeof(PriorityQueue)];
    int i;

    cout << "A. Testing that assignment operator works okay for empty queue...";
    cout << flush;
    PriorityQueue copy1;
    copy1.insert(1,1);
    copy1 = test;
    if (!correct(copy1, 0, items)) return 0;

    cout << "B. Testing assignment operator with 4-item queue...";
    cout << flush;
    test.insert(1, 100);
    test.insert(2, 50);
    test.insert(3, 25);
    test.insert(4, 10);
    PriorityQueue copy2;
    copy2 = test;
    test.insert(5, 80); // Alter the original, but not the copy
    if (!correct(copy2, 4, items)) return 0;

    cout << "C. Testing assignment operator for a self-assignment...";
    cout << flush;
    memcpy(oldbytes, &test, sizeof(PriorityQueue));
    test = test;
    memcpy(newbytes, &test, sizeof(PriorityQueue));
    for (i=0; i < sizeof(PriorityQueue); i++)
        if (oldbytes[i] != newbytes[i])
        {
            cout << "failed." << endl;
            return 0;
        }
    cout << "passed.\n";        
        
    cout << "Assignment operator seems okay." << endl;
    return POINTS[4];
}


int run_a_test(int number, const char message[], int test_function( ), int max)
{
    int result;
    
    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;
    
    return result;
}

// **************************************************************************
// int main( )
//   The main program calls all tests and prints the sum of all points
//   earned from the tests.
// **************************************************************************
int main( )
{
    int sum = 0;
    
    cout << "Running " << DESCRIPTION[0] << endl;

    sum += run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
    sum += run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
    sum += run_a_test(3, DESCRIPTION[3], test3, POINTS[3]);
    sum += run_a_test(4, DESCRIPTION[4], test4, POINTS[4]);

    cout << "If you submit this PriorityQueue now, you will have\n";
    cout << sum << " points out of the " << POINTS[0];
    cout << " points from this test program.\n";
    
    return EXIT_SUCCESS;

}