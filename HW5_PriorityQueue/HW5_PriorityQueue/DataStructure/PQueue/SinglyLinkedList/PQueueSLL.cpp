#include "PQueueSLL.h"
#include <iostream>

// Constructor, destructor
PQueueSLL::PQueueSLL()
{
    _head = nullptr;
}

PQueueSLL::~PQueueSLL()
{
    Object o;
    while (!this->isEmpty())
        extract(o);
    _head = nullptr;
    std::cout << "\nSuccessful queue deallocation.\n";
}

// Processing methods
bool PQueueSLL::isEmpty()
{
    bool isEmptyQueue = (_head == nullptr);
    return isEmptyQueue;
}

bool PQueueSLL::hadID(std::string id)
{
    for (Node *p = _head; p != nullptr; p = p->_next)
        if (id == p->_object._id)
            return 1;
    return 0;
}

bool PQueueSLL::insert(const Object &o)
{
    // If the given object's id exists, nothing will be inserted
    if (this->hadID(o._id))
        return 0;

    // If the given object's id does not exists:
    // Create a dummy head
    _head = new Node(Object("", "", 0), _head);

    // Double iterating
    Node *p2 = _head;
    Node *p1 = p2->_next;

    // Locate the right position to insert
    while (p1 != nullptr && p1->_object._priority < o._priority)
    {
        p2 = p1;
        p1 = p1->_next;
    }

    // Insert the given object into the found position
    Node *toInsertNode = new Node(o);
    p2->_next = toInsertNode;
    toInsertNode->_next = p1;

    // Remove the dummy head
    Node *dummyHead = _head;
    _head = _head->_next;
    delete dummyHead;
    return 1;
}

bool PQueueSLL::extract(Object &result)
{
    // Extract the first element of the linked list
    // The extracted object is returned in the passed-by-
    // reference parameter 'result'
    if (this->isEmpty())
        return 0;
    bool extracted = extractByID(_head->_object._id, result);
    return extracted;
}

bool PQueueSLL::remove(std::string id)
{
    // Extract the element by ID from the linked list
    // Not return the extracted object
    Object removee;
    bool extracted = extractByID(id, removee);
    return extracted;
}

bool PQueueSLL::changePriority(std::string id, int priority)
{
    Object toUpdateObj;
    bool extracted = extractByID(id, toUpdateObj);

    // If the given id does not exist, nothing will be updated
    if (!extracted)
        return 0;

    // If the given id exists:
    // Update the priority of the extracted one
    toUpdateObj._priority = priority;
    // Insert it back to the queue
    insert(toUpdateObj);
    return 1;
}

void PQueueSLL::print()
{
    if (this->isEmpty())
    {
        std::cout << "Empty queue.\n";
        return;
    }

    int i = 0;
    for (Node *p = _head; p != nullptr; p = p->_next)
    {
        std::cout << i++ << ". ";
        (p->_object).print();
    }
}

// Supporting method
bool PQueueSLL::extractByID(std::string id, Object &result)
{
    /*
    * This is a private method, which means it is accessible for struct
    scope only. Nowhere else in the program could the method be called.
    * It is implemented in order to support extracting and removing
    methods, because they have a lot in common. However, extracting by
    element's id is not a popular requirement for priority queue, so it
    is put in the private scope.
    */
    bool extracted = 0;
    if (this->isEmpty())
        return 0;

    // Create a dummy head
    _head = new Node(Object("", "", 0), _head);

    // Locate the node containing the given id
    Node *p2 = _head;
    Node *p1 = _head->_next;
    while (p1 != nullptr && p1->_object._id != id)
    {
        p1 = p1->_next;
        p2 = p2->_next;
    }

    // If the given id exists, extract the found object and
    // turn on the success flag. Else, the flag is still false
    if (p1 != nullptr)
    {
        p2->_next = p1->_next;
        result = p1->_object;
        delete p1;
        extracted = 1;
    }

    // Remove the dummy head
    Node *dummyHead = _head;
    _head = _head->_next;
    delete dummyHead;

    return extracted;
}
