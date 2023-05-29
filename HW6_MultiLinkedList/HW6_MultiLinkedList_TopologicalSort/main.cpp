#include <iostream>
#include <fstream>
using namespace std;
#include "Structs.h"
#include "Functions.h"

int main(){
    L_Ref l_head = NULL, l_tail = NULL;
    fstream f("input.txt", ios::in);
    int z = 0;
    
    readEdges(l_head, l_tail, f, z);
    releaseEdges(l_head, l_tail, z);

    f.close();
}
