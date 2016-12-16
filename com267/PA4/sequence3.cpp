#include "sequence3.h"
#include <iostream>

using namespace std;

namespace com267_sequence3 {
    sequence::sequence() {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    sequence::sequence(const sequence &source) {
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        if (source.precursor == NULL) {
            if (source.cursor == NULL) {
                cursor = NULL;
            } else {
                cursor = head_ptr;
            }
            precursor = NULL;
        } else {
            node *tmp_ptr = head_ptr;
            node *source_ptr = source.head_ptr;
            while (source_ptr != source.precursor) {
                source_ptr = source_ptr->link();
                tmp_ptr = tmp_ptr->link();
            }
            cursor = tmp_ptr->link();
            precursor = tmp_ptr;
        }
    }

    void sequence::operator=(const sequence &source) {
        if (this != &source) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            many_nodes = source.many_nodes;
            if (source.precursor == NULL) {
                if (source.cursor == NULL) {
                    cursor = NULL;
                } else {
                    cursor = head_ptr;
                }
                precursor = NULL;
            } else {
                node *tmp_ptr = head_ptr;
                node *source_ptr = source.head_ptr;
                while (source_ptr != source.precursor) {
                    source_ptr = source_ptr->link();
                    tmp_ptr = tmp_ptr->link();
                }
                cursor = tmp_ptr->link();
                precursor = tmp_ptr;
            }
        }
    }

    sequence::~sequence() {
        list_clear(head_ptr);
    }

    void sequence::start() {
        precursor = NULL;
        cursor = head_ptr;
    }

    void sequence::advance() {
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const sequence::value_type &entry) {
        if (is_item()) {
            if (precursor == NULL) {
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
            } else {
                list_insert(precursor, entry);
                cursor = precursor->link();
            }
        } else {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
        }
        many_nodes++;
    }

    void sequence::attach(const sequence::value_type &entry) {
        if (is_item()) {
            precursor = cursor;
            list_insert(cursor, entry);
            cursor = cursor->link();
        } else {
            if (head_ptr == NULL) {
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
            } else {
                precursor = list_locate(head_ptr, list_length(head_ptr));
                list_insert(precursor, entry);
                cursor = precursor->link();
            }
        }
        many_nodes++;
    }

    void sequence::remove_current() {
        if (cursor == head_ptr) {
            if (many_nodes == 1) {
                list_head_remove(head_ptr);
                cursor = NULL;
                head_ptr = NULL;
            } else {
                node *tmp = head_ptr;
                head_ptr = head_ptr->link();
                delete tmp;
                cursor = head_ptr;
            }
            precursor = NULL;
        } else {
            cursor = cursor->link();
            list_remove(precursor);
        }

        many_nodes--;
    }

    sequence::value_type sequence::current() const {
        return cursor->data();
    }

}