#include <iostream>
#include "Structs.h"
#include "Functions.h"

int main(){
    List* l = NULL;
    initList(l);
    addHead(l, 2); printList(l);                // tail = 2
    addHead(l, 3); printList(l);                // 3 -> tail = 2 
    addTail(l, 4); printList(l);                // 3 -> 2 -> tail = 4
    addHead(l, 5); printList(l);                // 5 -> 3 -> 2 -> tail = 4
    addTail(l, 6); printList(l);                // 5 -> 3 -> 2 -> 4 -> tail = 6
    addAfter(l, 5, 7); printList(l);            // 5 -> 7 -> 3 -> 2 -> 4 -> tail = 6
    removeTail(l); printList(l);                // 5 -> 7 -> 3 -> 2 -> tail = 4
    addAfter(l, 6, 8); printList(l);            // 5 -> 7 -> 3 -> 2 -> tail = 4
    addAfter(l, 2, 9); printList(l);            // 5 -> 7 -> 3 -> 2 -> 9 -> tail = 4
    removeHead(l); printList(l);                // 7 -> 3 -> 2 -> 9 -> tail = 4
    removeHead(l); printList(l);                // 3 -> 2 -> 9 -> tail = 4
    removeHead(l); printList(l);                // 2 -> 9 -> tail = 4
    removeHead(l); printList(l);                // 9 -> tail = 4
    removeHead(l); printList(l);                // tail = 4
    removeHead(l); printList(l);                // Empty list.
    removeHead(l); printList(l);                // Empty list.
    destroyList(l); printList(l);               // List uninitialized or destroyed.
}