#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include "Structs.h"

// head -> x -> x -> x -> ... -> x -> tail


void createLeaderList(L_Ref& l_head, L_Ref& l_tail) {
	l_head = new Leader;
	l_tail = new Leader;
	l_head->next = l_tail;
}

void deleteLeaderList(L_Ref& l_head, L_Ref& l_tail) {
	if (!l_head) delete l_head; l_head = NULL;
	if (!l_tail) delete l_tail; l_tail = NULL;
}

L_Ref addLeaderToLeaderList(L_Ref& l_head, L_Ref& l_tail, int val, int& z) {
	// h traverses from the first element (which is l_head->next)
	// the value w is set at l_tail, if w is new, we only need to create a new l_tail node
	L_Ref h = l_head->next;
	l_tail->key = val;
	while (h->key != val) h = h->next;
	// when w is a new value: increase the number of nodes (z)
	if (h == l_tail) {
		l_tail = new Leader;
		z++;
		h->count = 0;
		h->trail = NULL;
		h->next = l_tail;
		//cout << h->key << " " << h << endl;
	}
	return h;
}

void readEdges(L_Ref& l_head, L_Ref& l_tail, istream& f, int& z) {
	string edges; 
	f >> edges; 
	int pos0 = -1, pos1 = -1, pos2 = -1, x, y;
	createLeaderList(l_head, l_tail);

	do {
		pos0 = edges.find("(", pos0 + 1);
		pos1 = edges.find(",", pos1 + 1);
		pos2 = edges.find(")", pos2 + 1);
		if (pos0 != string::npos && pos0 <= edges.length()) {
			x = stoi(edges.substr(pos0 + 1, pos1 - pos0 - 1));
			y = stoi(edges.substr(pos1 + 1, pos2 - pos1 - 1));
			L_Ref p = addLeaderToLeaderList(l_head, l_tail, x, z);
			L_Ref q = addLeaderToLeaderList(l_head, l_tail, y, z);
			T_Ref t = new Trailer;
			t->id = q;
			t->next = p->trail;
			p->trail = t;
			q->count++;			
		}
		else
			break;
	} while (1);	
}

void releaseEdges(L_Ref& l_head, L_Ref& l_tail, int& z) {
	L_Ref p = l_head->next;
	L_Ref q;
	l_head = NULL;

	// Respectively insert independent nodes before l_head
	while (p != l_tail) {
		q = p;
		p = p->next;
		if (q->count == 0) {
			q->next = l_head;
			l_head = q;
		}
	}

	// q starts from the first independent node
	// After releasing that node, immediately insert its child nodes right at that position
	q = l_head;
	while (q) {
		cout << q->key << " ";
		z--;
		T_Ref t = q->trail;
		L_Ref tmp = q;
		q = q->next;
		delete tmp;
		while (t) {
			p = t->id;
			p->count--;
			if (p->count == 0) {
				p->next = q;
				q = p;
			}
			t = t->next;
		}
	} 
	cout << endl;
	deleteLeaderList(l_head, l_tail);
}
