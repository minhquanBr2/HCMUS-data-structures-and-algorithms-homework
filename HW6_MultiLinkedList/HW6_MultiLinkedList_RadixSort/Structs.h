#pragma once

typedef struct Trailer* T_Ref;
struct Trailer {
	int value;
	T_Ref next;
};

typedef struct Leader* L_Ref;
struct Leader {
	int key;
	int count;
	L_Ref next;
	T_Ref trail;
};