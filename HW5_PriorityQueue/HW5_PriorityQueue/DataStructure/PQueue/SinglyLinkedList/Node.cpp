#include "Node.h"

Node::Node(const Object &o, Node *next)
{
    _object = o;
    _next = next;
}
