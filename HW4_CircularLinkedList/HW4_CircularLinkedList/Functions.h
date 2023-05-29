#pragma once
#include "Structs.h"
#include <iostream>
using namespace std;

Ref createNode(int key) {
	Ref p = new Node;
	p->key = key;
	p->next = NULL;
	return p;
}
void initList(List*& l) {
	l = new List;
	l->tail = NULL;
}
void printList(List* l) {
	// List bị hủy
	if (!l) {
		cout << "List uninitialized or destroyed.\n";
		return;
	}
	// List trống: l->tail == NULL
	if (!l->tail) {
		cout << "Empty list.\n";
		return;
	}
	// List có phần tử
	Ref p = l->tail->next;
	do {
		cout << p->key << " ";
		p = p->next;
	} while (p != l->tail->next);
	cout << endl;
}
void destroyList(List*& l) {
	if (l->tail){
		Ref tail = l->tail;		// tail holds the value of l->tail, which will be lost after we delete l->tail. The do...while loop terminates if p reaches tail value.
		Ref p = l->tail;		// p traverses through the circular list.
		do {
			Ref p2 = p->next;
			delete p; 
			p = p2;
		} while (p != tail);
	}
	delete l;
	l = NULL;	
}

void addHead(List* l, int key) {
	Ref p = createNode(key);
	if (l->tail) {
		p->next = l->tail->next;
		l->tail->next = p;
	}
	else {
		l->tail = p;
		p->next = p;
	}
}
void addTail(List* l, int key) {
	Ref p = createNode(key);
	if (l->tail) {
		p->next = l->tail->next;
		l->tail->next = p;
		l->tail = p;
	}
	else {
		l->tail = p;
		p->next = p;
	}
}
void removeHead(List* l) {
	// Empty list
	if (!l || !l->tail) return;

	// list has 1 element: removeHead == removeTail
	if (l->tail->next == l->tail) {
		delete l->tail;
		l->tail = NULL;
	}
	// list more than 1 element
	else {
		Ref head = l->tail->next;
		l->tail->next = head->next;
		delete head;
	}	
}
void removeTail(List* l) {
	// Empty list
	if (!l || !l->tail) return;
	// list has 1 element: removeHead == removeTail
	if (l->tail->next == l->tail) {
		delete l->tail;
		l->tail = NULL;
	}
	// list more than 1 element
	else {		
		Ref new_tail = l->tail;			// Here to find new_tail as a replacement for tail
		while (new_tail->next != l->tail)
			new_tail = new_tail->next;
		new_tail->next = l->tail->next;
		delete l->tail;
		l->tail = new_tail;
	}	
}
Ref findKey(List* l, int key) {
	Ref p = l->tail->next;
	while (p->key != key && p != l->tail)
		p = p->next;
	if (p->key == key)
		return p;
	else
		return NULL;
}
void addAfter(List* l, int key, int key_to_be_added) {
	// For empty list, automatically addTail
	if (!l->tail) {
		addTail(l, key_to_be_added);
		return;
	}
	// Otherwise, only add new node if key is in the list
	Ref p = findKey(l, key);
	if (p) {
		// If p is exactly the tail node -> addTail()
		if (p == l->tail) {
			addTail(l, key_to_be_added);
			return;
		}
		// Otherwise, addNode as normal
		Ref temp = createNode(key_to_be_added);
		temp->next = p->next;
		p->next = temp;
	}
}
void removeAfter(List* l, int key) {
	Ref p = findKey(l, key);
	if (p)
		if (p->next == l->tail) removeTail(l);
		else if (p == l->tail) removeHead(l);
		else {
			Ref temp = p->next;
			p->next = p->next->next;
			delete temp;
		}
}
