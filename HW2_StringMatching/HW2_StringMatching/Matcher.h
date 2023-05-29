#pragma once
#include <string.h>
const int BASE = 256;
const int BM_SHIFT = 65;

class Matcher{
private: 
    static int* newLPSarray(const char*);
    static int* newBadMatchTable(const char*);
public:
    static int countBFmatch(const char*, const char*);
    static int countRKmatch(const char*, const char*);
    static int countKMPmatch(const char*, const char*);
    static int countBMmatch(const char*, const char*);
};
