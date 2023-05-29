#pragma once
#include "..\..\..\DataStructure\Object\Object.h"

struct Node
{
private:
    Object _object;
    Node *_next;

public:
    Node(const Object &o, Node *next = nullptr);
    friend struct PQueueSLL;
};
