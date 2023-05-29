#pragma once
#include "..\..\Object\Object.h"
#include "..\PQueue.h"
#include <vector>

/*
 * PQuereMH: Priority queue using min heap data structure .
 * PQueueMH is a struct inherited from struct PQueue.
 * Heap data structure in the program is vector-based.
 */

struct PQueueMH : public PQueue
{
private:
    std::vector<Object> _heap;

public:
    // Constructor and assignment operator
    PQueueMH(){};
    PQueueMH(const PQueueMH &p);
    PQueueMH &operator=(const PQueueMH &p);

    // Processing methods
    bool isEmpty();
    bool hadID(std::string id);
    bool insert(const Object &o);
    bool extract(Object &result);
    bool remove(std::string id);
    bool changePriority(std::string id, int priority);
    void print();

private:
    // Supporting methods
    bool extractByID(std::string id, Object &result);
    void sift(int l, int r);
};
