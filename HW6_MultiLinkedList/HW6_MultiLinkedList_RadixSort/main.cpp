#include <iostream>
#include <fstream>
#include "Structs.h"
#include "Functions.h"
using namespace std;

int main(){
    T_Ref t_head, t_tail;
    fstream f("input.txt", ios::in); 
    int k, n, d;
    f >> k >> n;    cout << k << " " << n << endl;

    readTrailerList(t_head, t_tail, n, f);
    d = countDigit(t_head, t_tail);
    radixSort(t_head, t_tail, k, d);
    printTrailerList(t_head, t_tail);

    f.close();
}
