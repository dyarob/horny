#ifndef GROUP_H
#define GROUP_H

#include "vector.h"

typedef struct cell {
	char i;
	char j;
	struct cell *next;
} cell;

typedef struct group {
	char weight;
	cell *list;
	struct group *next;
} group;

#endif
