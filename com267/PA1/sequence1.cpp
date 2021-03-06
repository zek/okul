//
// Created by Talha Zekeriya Durmuş on 15/10/2016.
//

#include "sequence1.h"
#include <iostream>

using namespace std;

namespace com267_sequence {

//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
//   static const size_type CAPACITY = _____
//     sequence::CAPACITY is the maximum number of items that a sequence can hold.

    /*
     * Postcondition: The sequence has been initialized as an empty sequence.
     */
    sequence::sequence() {
        this->used = 0;
        this->current_index = 0;
    }

    /*
     * Postcondition: The first item on the sequence becomes the current item
     * (but if the sequence is empty, then there is no current item).
     */
    void sequence::start() {
        this->current_index = 0;
    }

    /*
     * Precondition: is_item returns true.
     * Postcondition: If the current item was already the last item in the
     * sequence, then there is no longer any current item. Otherwise, the new
     * current item is the item immediately after the original current item.
     */
    void sequence::advance() {
        if (current_index >= used) {
            current_index = used;
        } else {
            current_index++;
        }
    }

    /**
     * Precondition: size( ) < CAPACITY.
     * Postcondition: A new copy of entry has been inserted in the sequence
     * before the current item. If there was no current item, then the new entry
     * has been inserted at the front of the sequence. In either case, the newly
     * inserted item is now the current item of the sequence.
     */
    void sequence::insert(const value_type &entry) {
        size_type target_index = is_item() ? current_index : 0;
        for (size_type i = used; i > target_index; i--)
            data[i] = data[i - 1];
        used++;
        current_index = target_index;
        data[current_index] = entry;
    }

    /**
     * Precondition: size( ) < CAPACITY.
     * Postcondition: A new copy of entry has been inserted in the sequence after
     * the current item. If there was no current item, then the new entry has
     * been attached to the end of the sequence. In either case, the newly
     * inserted item is now the current item of the sequence.
     */
    void sequence::attach(const value_type &entry) {
        if (is_item()) {
            for (size_type i = used; i > current_index + 1; i--)
                data[i] = data[i - 1];
            used++;
            current_index++;
        } else {
            used++;
            current_index = used - 1;
        }
        data[current_index] = entry;
    }

    /**
     * Precondition: is_item returns true.
     * Postcondition: The current item has been removed from the sequence, and the
     * item after this (if there is one) is now the new current item.
     */
    void sequence::remove_current() {
        for (size_type i = current_index; i < used - 1; i++)
            data[i] = data[i + 1];
        used--;
    }

    /*
     * Postcondition: The return value is the number of items in the sequence
     */
    sequence::size_type sequence::size() const {
        return used;
    }

    /**
     * Postcondition: A true return value indicates that there is a valid
     * "current" item that may be retrieved by activating the current
     * member function (listed below). A false return value indicates that
     * there is no valid current item.
     */
    bool sequence::is_item() const {
        return current_index < used;
    }

    /**
     * Precondition: is_item( ) returns true.
     * Postcondition: The item returned is the current item in the sequence.
     */
    sequence::value_type sequence::current() const {
        return data[current_index];
    }
}
