#include "PQueue_UI.h"
#include "..\DataStructure\PQueue\MinHeap\PQueueMH.h"
#include "..\DataStructure\PQueue\SinglyLinkedList\PQueueSLL.h"
#include "Defines.h"
#include <iostream>

using std::cin;
using std::cout;

/*
    * Thanks to the inheritance and polymorphism of object oriented
    programming, it is unneccessary to implement user interface methods
    for min heap based prioriry queue and singly linked list priority
    queue separately. They have fundamental operations in common which
    is described in the abstract struct PQueue, so any PQueue_UI object
    which has a pointer to PQueue is able to handle a PQueueMH (min
    heap based), or a PQueueSLL (singly linked list based).
*/

// Destructor
PQueue_UI::~PQueue_UI()
{
    delete _pQueueHandle;
}

// Menu
void PQueue_UI::showInitializingMenu()
{
    char option = EXIT;

    cout << "Initializing menu:\n\t"
         << MINHEAP << " - min heap\n\t"
         << SLLIST << " - singly linked list\n\t"
         << EXIT << " - exit\n";

    cout << "Your option: ";
    cin >> option;

    switch (option)
    {
    case MINHEAP:
        _pQueueHandle = new PQueueMH;
        break;
    case SLLIST:
        _pQueueHandle = new PQueueSLL;
        break;
    default:
        exit(1);
    }
}

void PQueue_UI::showProcessingMenu()
{
    char option = EXIT;
    while (true)
    {
        cout << "Processing menu:\n\t"
             << INSERT << " - insert\n\t"
             << EXTRACT << " - extract\n\t"
             << REMOVE << " - remove\n\t"
             << UPDATE << " - update\n\t"
             << PRINT << " - print\n\t"
             << EXIT << " - exit\n";

        cout << "Your option: ";
        cin >> option;

        switch (option)
        {
        case INSERT:
            this->insert();
            break;
        case EXTRACT:
            this->extract();
            break;
        case REMOVE:
            this->remove();
            break;
        case UPDATE:
            this->changePriority();
            break;
        case PRINT:
            this->print();
            break;
        default:
            return;
        }
        cout << "\t------------------\n";
    };
}

// Processing methods
void PQueue_UI::checkEmpty()
{
    bool isEmptyQueue = _pQueueHandle->isEmpty();
    if (isEmptyQueue)
        cout << "The queue is empty.\n";
    else
        cout << "The queue is not empty.\n";
}

void PQueue_UI::insert()
{
    Object o;
    o.scan();
    bool inserted = _pQueueHandle->insert(o);
    if (inserted)
        cout << "Successful insertion.\n";
    else
        cout << "Unsuccessful insertion (identical ID found).\n";
}

void PQueue_UI::extract()
{
    Object o;
    bool extracted = _pQueueHandle->extract(o);
    if (extracted)
    {
        cout << "Successful extraction.\n";
        cout << "Extracted object's information:\n";
        o.print();
    }
    else
        cout << "Unsuccessful extraction (empty queue).\n";
}

void PQueue_UI::remove()
{
    std::string toRemoveID = "0";
    cout << "Enter to-remove ID: ";
    cin >> toRemoveID;
    bool removed = _pQueueHandle->remove(toRemoveID);
    if (removed)
        cout << "Successful removal.\n";
    else
        cout << "Unsuccessful removal (ID not found).\n";
}

void PQueue_UI::changePriority()
{
    std::string toUpdateID = "";
    int toUpdatePriority = 0;
    cout << "Enter to-update ID: ";
    cin >> toUpdateID;
    cout << "Enter to-update priority: ";
    cin >> toUpdatePriority;

    bool updated = _pQueueHandle->changePriority(toUpdateID, toUpdatePriority);
    if (updated)
        cout << "Successful update.\n";
    else
        cout << "Unsuccessful update (ID not found).\n";
}

void PQueue_UI::print()
{
    _pQueueHandle->print();
}
