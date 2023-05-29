#pragma once

typedef struct Leader* L_Ref;
typedef struct Trailer* T_Ref;

struct Leader {
	int key;
	int count;
	L_Ref next;
	T_Ref trail;
};

struct Trailer {
	L_Ref id;
	T_Ref next;
};