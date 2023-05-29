#pragma once
#include "..\DataStructure\Trie.h"

struct FileHandle
{
private:
    Trie *_trieHandle;

public:
    FileHandle();
    ~FileHandle();

    bool read(string inputFile);
    bool write(string outputFile);

    friend class TrieUI;
};
