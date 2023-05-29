#pragma once
#include "..\Object\Object.h"
#include <vector>
#include <iostream>

/*
    * PQueue: abstract struct for priority queue.

    * Object oriented struct provides inheritance and polymorphism, which
    is useful here, because except for the basic logic of data structure,
    they serve the same operations. Using object oriented programming
    here helps generalize the program and reduce code redundancy.
*/

struct PQueue
{
public:
    // Constructor, Destructor
    PQueue(){};
    virtual bool isEmpty() = 0;
    virtual bool hadID(std::string id) = 0;
    virtual bool insert(const Object &o) = 0;
    virtual bool extract(Object &result) = 0;
    virtual bool remove(std::string id) = 0;
    virtual bool changePriority(std::string id, int priority) = 0;
    virtual void print() = 0;

private:
    virtual bool extractByID(std::string id, Object &result) = 0;
};
