// FILE: pqueue1.h

// CLASS PROVIDED: PriorityQueue (a priority queue of items)
//
// TYPEDEF for the PriorityQueue class:
//   typedef _____ Item 
//     The type Item is the data type of the items in the Priority Queue.
//     It may be any of the C++ built-in types (int, char, etc.), or a class 
//     with a default constructor, a copy constructor, and assignment operator.
//
// CONSTRUCTOR for the PriorityQueue class:
//   PriorityQueue( )
//     Postcondition: The PriorityQueue has been initialized with no Items.
//
// MODIFICATION MEMBER FUNCTIONS for the PriorityQueue class:
//   void insert(const Item& entry, unsigned int priority)
//     Postcondition: A new copy of entry has been inserted with the specified
//     priority.
//
//   Item get_front( )
//     Precondition: size( ) > 0.
//     Postcondition: The highest priority item has been returned and has been
//     removed from the PriorityQueue. (If several items have equal priority,
//     then the one that entered first will come out first.)
//
// CONSTANT MEMBER FUNCTIONS for the PriorityQueue class:
//   size_t size( ) const
//     Postcondition: Return value is the total number of items in the
//     PriorityQueue.
//
//   bool is_empty( ) const
//     Postcondition: Return value is true if the PriorityQueue is empty.
//
// VALUE SEMANTICS for the PriorityQueue class:
//   Assignments and the copy constructor may be used with
//   PriorityQueue objects

#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdlib.h> // Provides size_t

    struct Node; // This will be completely defined below.

    class PriorityQueue
    {
    public:
        typedef int Item;
        PriorityQueue( );
        PriorityQueue(const PriorityQueue& source);
        ~PriorityQueue( );
        void operator =(const PriorityQueue& source);
        size_t size( ) const;
        void insert(const Item& entry, unsigned int priority);
        Item get_front( );
        bool is_empty( ) const;

        // student must list all the prototypes here including
        // the copy constructor, assignment operator, and destructor
    private:
        // Note: head_ptr is the head pointer for a linked list that
        // contains the items along with their priorities. These nodes are
        // kept in order from highest priority (at the head of the list)
        // to lowest priority (at the tail of the list). The private member
        // variable, many_nodes, indicates how many nodes are on the list.
        // The data type Node is completely defined below.
        Node *head_ptr;
        size_t many_nodes;


    };

    struct Node
    {   // Node for a linked list
        PriorityQueue::Item data;
        unsigned int priority;
        Node *link;
    };

#endif