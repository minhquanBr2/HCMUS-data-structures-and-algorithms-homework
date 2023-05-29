#include "FileHandle.h"

#include "..\DataStructure\TrieNode.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::fstream;
using std::ios;

FileHandle::FileHandle()
{
    _trieHandle = new Trie;
}

FileHandle::~FileHandle()
{
    _trieHandle->~Trie();
}

bool FileHandle::read(string filename)
{
    fstream f;
    f.open(filename, ios::in);
    if (!f.good())
        return 0;

    int id = 0;
    while (!f.eof())
    {
        string word;
        f >> word;
        _trieHandle->insert(word, id++);
    }

    f.close();
    return 1;
}

bool FileHandle::write(string filename)
{
    if (_trieHandle == nullptr)
        return 0;

    fstream f;
    f.open(filename, ios::out);
    if (!f.good())
        return 0;

    f << *_trieHandle;
    f.close();
    return 1;
}
