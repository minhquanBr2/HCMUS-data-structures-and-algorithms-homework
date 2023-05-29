#include "Matcher.h"
#include <math.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

// PRIVATE METHODS
int* Matcher::newLPSarray(const char* pattern) {
    // Longest Prefix Suffix
    int pLen = strlen(pattern);
    int* LPS = new int [pLen]{0};
    int matchLen = 0;

    int i = 1;
    while (i < pLen) {
        if (pattern[i] != pattern[matchLen]) {
            if (matchLen != 0) matchLen = LPS[matchLen - 1];
            else LPS[i++] = 0;
        }
        else LPS[i++] = ++matchLen;
    }

    return LPS;
} 

int* Matcher::newBadMatchTable(const char* pattern) {
    int pLen = strlen(pattern);
    int* BMT = new int[58];                         // from 'A' to 'z'
    int val;

    for (int i = 0; i < 58; i++) BMT[i] = pLen + 1; // distinct value for all letters which don't exist in pattern string

    for (int i = pLen - 1; i >= 0; i--)
        if (BMT[pattern[i] - BM_SHIFT] == pLen + 1)
            BMT[pattern[i] - BM_SHIFT] = pLen - 1 - i;
    BMT[pattern[pLen - 1] - BM_SHIFT] = pLen;

    return BMT;

}

// PUBLIC METHODS
int Matcher::countBFmatch(const char* main, const char* pattern) {
    int count = 0;
    
    int mLen = strlen(main);
    int pLen = strlen(pattern);

    for (int i = 0; i <= mLen - pLen; ++i) {
        int j = 0;
        while (j < pLen && pattern[j] == main[i + j] && ++j);
        if (j == pLen) count++;
    }

    return count;
}  

int Matcher::countRKmatch (const char* main, const char* pattern) {
    int count = 0;
    int mLen = strlen(main);
    int pLen = strlen(pattern);
    
    unsigned long long mHashCode = 0;
    unsigned long long pHashCode = 0;

    // Calculate the very first hash codes
    for (int i = 0; i < pLen; ++i) {
        // Be careful with pow() which can return approximate value ...
        mHashCode = mHashCode + main[i] * round(pow(BASE, pLen - i - 1));
        pHashCode = pHashCode + pattern[i] * round(pow(BASE, pLen - i - 1));
    }

    if (mHashCode == pHashCode) count++;

    // Rolling hash code ...
    unsigned long long highestPow = round(pow(BASE, pLen - 1));
    for (int i = pLen; i < mLen; ++i) {
        mHashCode = (mHashCode - main[i - pLen] * highestPow) * BASE + main[i];
        if (mHashCode == pHashCode) count++;
    }

    return count;
}

int Matcher::countKMPmatch(const char* main, const char* pattern) {
    int count = 0;

    int mLen = strlen(main);
    int pLen = strlen(pattern);
    int* LPS = newLPSarray(pattern);
    
    int i = 0, j = -1;
    while (mLen - i >= pLen - j - 1) {
        if (main[i] == pattern[j + 1]) {i++; j++;}
        if (j == pLen - 1) {count++; j = LPS[j] - 1;}
        else if (i < mLen && main[i] != pattern[j + 1])
            if (j != -1) j = LPS[j] - 1;
            else { i++;}
    }

    delete[] LPS;
    return count;
}

int Matcher::countBMmatch(const char* main, const char* pattern) {
    int count = 0;
    int mLen = strlen(main);
    int pLen = strlen(pattern);

    int* BMT = newBadMatchTable(pattern);
    int i = 0, p1, p2;
    while (i + pLen - 1 < mLen) {
        if (BMT[main[i + pLen - 1] - BM_SHIFT] == pLen + 1) {
            i += pLen;                      // Jump to next substring, number of steps based on BMT
        }
        else {
            p1 = i + pLen - 1;              // End of letter chunk
            p2 = pLen - 1;                  // End of pattern
            while (p2 >= 0 && main[p1] == pattern[p2]) {
                
                p1--;
                p2--;
            }
            if (p2 < 0) count++;                    // Correctly checked pattern string with substring of main
            i += BMT[main[i + pLen - 1] - BM_SHIFT];   // Jump to next substring, number of steps based on BMT
        }
    };

    delete[] BMT;
    return count;


}

