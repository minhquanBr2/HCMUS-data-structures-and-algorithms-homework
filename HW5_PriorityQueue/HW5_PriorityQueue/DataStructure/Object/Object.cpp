#include "Object.h"
#include <iostream>
using std::cin;
using std::cout;

// Constructor
Object::Object(string id, string order, int priority)
{
    _id = id;
    _order = order;
    _priority = priority;
}

// IO methods
void Object::print()
{
    cout << "Id = " << _id << ", "
         << "Or = " << _order << ", "
         << "Pr = " << _priority << "\n";
}

void Object::scan()
{
    cout << "ID = ";
    cin >> _id;
    cout << "Order = ";
    cin >> _order;
    cout << "Priority = ";
    cin >> _priority;
}

// Processing method
void Object::swap(Object &swapper)
{
    Object temp = *this;
    *this = swapper;
    swapper = temp;
}
