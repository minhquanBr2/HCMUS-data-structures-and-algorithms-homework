#pragma once
#include <iostream>
#include <math.h>
#include "Structs.h"
using namespace std;

int getKey(int value, int j, int k) {
	int range = (int)pow(10, k);
	int key = value / pow(range, j);
	key = key % range;
	return key;
}

int countDigit(T_Ref& t_head, T_Ref& t_tail) {
	T_Ref h = t_head->next;
	while (h != t_tail) h = h->next;
	return (int)(1 + log10(h->value));
}



T_Ref createTrailer(int value) {
	T_Ref t = new Trailer;
	t->value = value;
	t->next = NULL;
	return t;
}

void addTrailerToTrailerList(T_Ref& t_head, T_Ref& t_tail, T_Ref& t) {
	T_Ref h = t_head;
	while (h->next != t_tail) h = h->next;
	h->next = t;
	t->next = t_tail;
}

void readTrailerList(T_Ref& t_head, T_Ref& t_tail, int n, fstream& f) {
	int value;
	t_head = createTrailer(INT_MIN);
	t_tail = createTrailer(INT_MAX);
	t_head->next = t_tail;

	while (n > 0) {
		f >> value;
		T_Ref t = createTrailer(value);
		addTrailerToTrailerList(t_head, t_tail, t);
		n--;
	}
}

void printTrailerList(T_Ref& t_head, T_Ref& t_tail) {
	T_Ref h = t_head->next;
	while (h != t_tail) {
		cout << h->value << " ";
		h = h->next;
	}
	cout << endl;
}

void deleteTrailerList(T_Ref& t_head) {
	T_Ref h = t_head, tmp;
	while (h) {
		tmp = h->next;
		delete h;
		h = tmp;
	}
}



L_Ref createLeader(int key) {
	L_Ref l = new Leader;
	l->key = key;
	l->count = 0;
	l->next = NULL;
	l->trail = NULL;
	return l;
}

void addTrailerToLeaderList(T_Ref x, L_Ref& l_head, L_Ref& l_tail, int j, int k) {
	int key = getKey(x->value, j, k);
	L_Ref h = l_head;
	// Comparison condition: if there is any new element, h will be the preceding element of new, therefore key must be less than h->next->key.
	// h = l_head means that the new element is inserted at the beginning of the list.
	while (h->next != l_tail && key >= h->next->key)
		h = h->next;

	// Add a number with already existed key to Leader list
	if (h != l_head && h->key == key) {
		h->count++;
		T_Ref t = h->trail;
		while (t->next != NULL) t = t->next;
		t->next = x;
		x->next = NULL;
	}
	// Add a number with brand new key to Leader list
	else {
		L_Ref newLeader = createLeader(key);
		L_Ref tmp = h->next;
		h->next = newLeader;
		newLeader->next = tmp;
		newLeader->count++;
		newLeader->trail = x;
		x->next = NULL;
	}
}

void deleteLeaderList(L_Ref& l_head) {
	L_Ref h = l_head, tmp;
	while (h) {
		tmp = h->next;
		delete h;
		h = tmp;
	}
}



void radixSort(T_Ref& t_head, T_Ref& t_tail, int k, int d) {

	for (int j = 0; j <= (d - 1) / k; j++) {
		// Each time using radixSort, we must create a new leader list for easier management of elements
		L_Ref l_head = createLeader(INT_MIN);
		L_Ref l_tail = createLeader(INT_MAX);
		l_head->next = l_tail;

		// After adding t1 to the Leader list, we'll lose track of its succeeding element
		// Therefore we use t2 to save its position for future use.
		T_Ref t1 = t_head->next;
		T_Ref t2 = t_head->next->next;

		// Remember that t_head still points to t_head->next, so we must alter its "next" field to points to l_tail
		while (t2 != NULL) {
			addTrailerToLeaderList(t1, l_head, l_tail, j, k);
			t1 = t2;
			t2 = t2->next;
		}
		t_head->next = t_tail;

		// For each leader, add all of its trailers to the original trailer list.
		L_Ref h = l_head->next;
		while (h != l_tail) {
			T_Ref t = h->trail; 
			while (t) {
				T_Ref tmp = t->next;
				addTrailerToTrailerList(t_head, t_tail, t);
				t = tmp;
			}
			h = h->next;
		}

		deleteLeaderList(l_head);
	}
}
