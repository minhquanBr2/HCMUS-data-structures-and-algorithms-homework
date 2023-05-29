#include "PQueueMH.h"
#include "..\..\Object\Object.h"
#include <iostream>
#include <math.h>

/* Copy constructor and assignment operator */
PQueueMH::PQueueMH(const PQueueMH &p)
{
    // Copy constructor to initialize a PQueueMH
    // object from a given PQueueMH object 'p'
    int size = p._heap.size();
    for (int i = 0; i < size; ++i)
        _heap.push_back(p._heap[i]);
}

PQueueMH &PQueueMH::operator=(const PQueueMH &p)
{
    // Assign a given PQueueMH object 'p' to one PQueueMH object
    int size = p._heap.size();
    for (int i = 0; i < size; ++i)
        _heap.push_back(p._heap[i]);
    return *this;
}

// Processing methods
bool PQueueMH::isEmpty()
{
    bool isEmptyQueue = _heap.empty();
    return isEmptyQueue;
}

bool PQueueMH::hadID(std::string id)
{
    int size = _heap.size();
    for (int i = 0; i < size; ++i)
        if (_heap[i]._id == id)
            return 1;
    return 0;
}

bool PQueueMH::insert(const Object &o)
{
    // If id of the given object exists, return 0
    if (this->hadID(o._id))
        return 0;

    // Push the object to the end of the vector
    _heap.push_back(o);
    int size = _heap.size();
    if (size > 1)
    {
        // Heapify the whole priority queue by gradually
        // sifting elements from size/2 forwards (extends
        // the natural heap region.)
        for (int i = size / 2; i >= 0; --i)
            sift(i, size - 1);
    }
    return 1;
}

bool PQueueMH::extract(Object &result)
{
    // Extract the top element of the min heap (_heap[0])
    // The extracted object is returned in the passed-by-
    // reference parameter 'result'
    bool extracted = this->extractByID(_heap[0]._id, result);
    return extracted;
}

bool PQueueMH::remove(std::string id)
{
    Object removee;
    // Extract the element by ID from the heap
    // Not return the extracted object
    bool extracted = this->extractByID(id, removee);
    return extracted;
}

bool PQueueMH::changePriority(std::string id, int priority)
{
    Object toUpdateObj;
    // Extract the object that has the given id
    bool extracted = this->extractByID(id, toUpdateObj);
    // If the extraction fails (id not found), return false
    if (!extracted)
        return 0;
    // If the extraction is successful:
    // Update the priority of the extracted one
    toUpdateObj._priority = priority;
    // Insert it back to the queue
    this->insert(toUpdateObj);
    return 1;
}

void PQueueMH::print()
{
    if (this->isEmpty())
    {
        std::cout << "Empty queue.\n";
        return;
    }

    // Create a copy
    PQueueMH temp = *this;
    Object extractee;
    while (!(temp.isEmpty()))
    {
        // Extract element by element in the copy priority
        // queue and print it out to the screeen.
        temp.extract(extractee);
        extractee.print();
    }
    std::cout << "\n";
}

// Private supporting methods
void PQueueMH::sift(int l, int r)
{
    /*
        * Sift method 'inserts' the element 'l' into heap-satisfying region
        from l + 1 to r (r is often the end of the heap data structure)
        * Note: The region from size/2 backwards is called natural heap, a
        default heap-satisfying region.
    */

    int parent = l;
    // Get the object of the to-sift element
    Object rootValue = _heap[l];
    // Identify its first child
    int child = 2 * parent + 1;

    while (child <= r) // While in heap's scope
    {
        // Let 'child' be the element whose priority is smaller
        // (if 'parent' has 2 children).
        if (child < r && _heap[child]._priority > _heap[child + 1]._priority)
            child++;
        // If parent's priority is smaller than the chosen child,
        // it meets heap requirement; therefore, end the loop.
        if (rootValue._priority <= _heap[child]._priority)
            break;
        // If parent's priority is not smaller than the chosen child,
        // swap them and continue to sift until 'l' meets heap requirement.
        _heap[parent].swap(_heap[child]);
        parent = child;
        child = 2 * parent + 1;
    }
}

bool PQueueMH::extractByID(std::string id, Object &result)
{
    /*
        * This is a private method, which means it is accessible for struct
        scope only. Nowhere else in the program could the method be called.
        * It is implemented in order to support extracting and removing
        methods, because they have a lot in common. This method will be
        wrapped, punlic to users. The original version is kept private.
    */
    if (this->isEmpty())
        return 0;

    // Locate
    int size = _heap.size();
    int i = 0;
    while (i < size && _heap[i]._id != id)
        i++;

    // If the ID does not exists, nothing will be extracted
    if (i == size)
        return 0;

    // If the ID exists, get the to-extract object, replace
    // it with the last element, and sift from the current
    // position to the end of the new heap (the right boundary
    // is reduced by 1 now, so it is (size - 1) - 1)
    result = _heap[i];
    _heap[i] = _heap[size - 1];
    _heap.pop_back();
    this->sift(i, size - 2);
    return 1;
}
