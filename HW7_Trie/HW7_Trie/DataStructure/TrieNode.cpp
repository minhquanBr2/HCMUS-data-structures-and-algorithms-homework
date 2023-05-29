#include "TrieNode.h"

TrieNode::TrieNode()
{
    _id = DEFAULT_ID;
}

TrieNode::TrieNode(int id)
{
    _id = id;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        _next[i] = nullptr;
}

TrieNode::~TrieNode()
{
    this->remove();
}

void TrieNode::remove()
{
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (_next[i] != nullptr)
            {
                _next[i]->remove();
                _next[i] = nullptr;
            }
    }
}

int TrieNode::countChildren()
{
    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (_next[i] != nullptr)
            count++;
    return count;
}
