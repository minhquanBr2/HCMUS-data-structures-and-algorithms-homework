#pragma once
#include <string>
using std::string;

struct Object
{
private:
    string _id;
    string _order;
    int _priority;

public:
    // Constructors
    Object(){}; // Default constructor
    Object(string id, string order, int priority);

    // Input/Output methods
    void print();
    void scan();

    // Processing method
    void swap(Object &swapper);

    // Friend declarartion
    friend struct Node;
    friend struct PQueue;
    friend struct PQueueSLL;
    friend struct PQueueMH;
};
