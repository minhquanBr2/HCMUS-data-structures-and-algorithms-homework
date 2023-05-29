#include <iostream>
#include "sort.h"
using std::cout;

/*
    * argv[0]: executable filename
    * argv[1]: find value
    * argv[2+]: integer array
*/

int main(int argc, char **argv) {
    if (argc < 3) return 1;

    // FROM ARGUMENT VALUES TO USEFUL DATA
    int size = argc - 2;
    int findValue = atoi(argv[1]);

    // TRANSFORM INPUT ARRAY FROM CHAR TO INTEGER
    int* arr = new int [size];
    for(int i = 0; i < size; ++i) 
        arr[i] = atoi(argv[i + 2]);

    // INTERPOLATION SEARCH
    int count = 0;
    cout << interpolationSearch(arr, size, findValue, count) + 1;       // Giả sử dãy số có index đếm từ 1
    cout << " - " << count;

    delete[] arr;
    return 0;
}