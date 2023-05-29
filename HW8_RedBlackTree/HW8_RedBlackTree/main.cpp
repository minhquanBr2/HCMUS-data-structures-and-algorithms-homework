#include "RBNode.h"
#include "common.h"

RBRef nil = new RBNode(0, BLACK, nil, nil, nil);

int main(){
    *nil = RBNode(0, BLACK, nil, nil, nil);

    int a[] = {1, 9, 5, 4, 5, 11, 12, 13, 16};
    int n = sizeof(a) / sizeof(a[0]);

    RBRef pRoot = createTree(a, n);

    RBRef foundNode = lookUp(pRoot, 26);
    int height = Height(pRoot);
    int blackHeight = BlackHeight(pRoot);

    print2D(pRoot);

    removeTree(pRoot);
    return 0;
}
