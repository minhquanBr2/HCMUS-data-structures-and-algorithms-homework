#include "sort.h"

int interpolationSearch(int* arr, int size, int val, int& count) {
    count = 0;
    int l = 0, r = size - 1;
    while (l <= r) {
        count++;
        int key = l + (val - arr[l]) * (r - l) / (arr[r] - arr[l]);
    
        if (arr[key] == val) return key;
        if (arr[key] < val) l = key + 1;
        else if (arr[key] > val) r = key - 1;
    }
    return -1;
}