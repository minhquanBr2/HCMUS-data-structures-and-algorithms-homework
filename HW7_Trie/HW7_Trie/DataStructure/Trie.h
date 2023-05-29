#pragma once
#include "TrieNode.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

struct Trie
{
private:
    TrieNode *_root;

public:
    Trie();
    ~Trie();

    bool insert(string word, int id);
    int lookUp(string word);
    vector<string> lookUpPrefix(string prefix);
    bool remove(string word);

    friend ostream &operator<<(ostream &os, Trie &trie);

private:
    void DFT(TrieNode *start, vector<string> &result, string curWord);
};
