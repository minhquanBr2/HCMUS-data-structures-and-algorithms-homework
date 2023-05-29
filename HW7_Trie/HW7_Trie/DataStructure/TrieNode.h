#pragma once
#include <string>

#define ALPHABET_SIZE 26
#define DEFAULT_ID -1

struct TrieNode
{
    int _id;
    TrieNode *_next[ALPHABET_SIZE] = {nullptr};

public:
    TrieNode();
    TrieNode(int id);
    ~TrieNode();

    int countChildren();
    void remove();

    TrieNode(const TrieNode &n) = delete;
    TrieNode &operator=(const TrieNode &n) = delete;
};
