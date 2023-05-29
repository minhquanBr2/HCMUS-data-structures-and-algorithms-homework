#pragma once

typedef struct Node* Ref;
struct Node {
	int key;
	Ref next;
};

struct List {
	Ref tail;
};
