#pragma once
#include "..\PQueue.h"
#include "Node.h"

/*
 * PQuereSLL: Priority queue using singly linked list.
 * PQueueSLL is a struct inherited from struct PQueue.
 */

struct PQueueSLL : public PQueue
{
private:
    Node *_head;

public:
    PQueueSLL();  // Default constructor
    ~PQueueSLL(); // Destructor (deallocate memory)

    // Processing methods
    bool isEmpty();
    bool hadID(std::string id);
    bool insert(const Object &o);
    bool extract(Object &result);
    bool remove(std::string id);
    bool changePriority(std::string id, int priority);
    void print();

private:
    // Supporting method
    bool extractByID(std::string id, Object &result);
};
