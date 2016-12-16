#include "pqueue1.h"
#include <iostream>

using namespace std;

PriorityQueue::PriorityQueue() {
    head_ptr = NULL;
    many_nodes = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue &source) {
    if (source.head_ptr == NULL) {
        head_ptr = NULL;
        many_nodes = 0;
    } else {
        Node *q = new Node;
        head_ptr = q;
        many_nodes = source.many_nodes;
        Node *cursor = source.head_ptr;
        while (cursor != NULL) {
            q->data = cursor->data;
            q->priority = cursor->priority;
            if (cursor->link != NULL) {
                Node *ptr = new Node;
                q->link = ptr;
                q = q->link;
            }
            cursor = cursor->link;
        }
        q->link = NULL;
    }
}

PriorityQueue::~PriorityQueue() {
    Node *h;
    h = head_ptr;
    while (h != NULL) {
        Node *q;
        q = h;
        h = h->link;
        delete q;
    }

}

void PriorityQueue::operator=(const PriorityQueue &source) {
    if (this != &source) {
        Node *cursor = head_ptr, *q;
        while (cursor != NULL) {
            head_ptr = cursor;
            cursor = head_ptr->link;
            delete head_ptr;
        }
        head_ptr = NULL;
        many_nodes = 0;
        if (source.head_ptr != NULL) {
            q = new Node;
            head_ptr = q;
            many_nodes = source.many_nodes;
            cursor = source.head_ptr;
            while (cursor != NULL) {
                q->data = cursor->data;
                q->priority = cursor->priority;
                if (cursor->link != NULL) {
                    Node *ptr = new Node;
                    q->link = ptr;
                    q = q->link;
                }
                cursor = cursor->link;
            }
            q->link = NULL;
        }
    }
}




void PriorityQueue::insert(const PriorityQueue::Item &entry, unsigned int priority) {
    Node *cursor = head_ptr, *after = NULL;
    Node *new_node = new Node;
    new_node->data = entry;
    new_node->priority = priority;
    new_node->link = NULL;
    while (true) {
        if (cursor != NULL) {
            if (priority > cursor->priority) {
                new_node->link = cursor;
                if (after == NULL) {
                    head_ptr = new_node;
                } else {
                    after->link = new_node;
                }
                break;
            } else {
                after = cursor;
                cursor = cursor->link;
            }
        } else {
            if (after == NULL) {
                head_ptr = new_node;
            } else {
                after->link = new_node;
            }
            break;
        }
    }
    many_nodes++;
    return;
}

PriorityQueue::Item PriorityQueue::get_front() {
    Node *h = head_ptr;
    head_ptr = head_ptr->link;
    Item d = h->data;
    many_nodes--;
    delete h;
    return d;
}

size_t PriorityQueue::size() const {
    return many_nodes;
}

bool PriorityQueue::is_empty() const {
    return many_nodes == 0;
}
