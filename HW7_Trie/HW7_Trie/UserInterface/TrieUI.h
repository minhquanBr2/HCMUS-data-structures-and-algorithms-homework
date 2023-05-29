#pragma once
#include "FileHandle.h"

struct TrieUI
{
private:
    FileHandle *_fileHandle;

public:
    TrieUI();
    ~TrieUI();

    // Menu
    void showMenu();

    // Processing methods
    void readfile();
    void writefile();

    void insert();
    void lookUp();
    void lookUpPrefix();
    void remove();
    void print();
};
