#ifndef RLIST_H

#define RLIST_H 1

#include "rover.h"
#include <stdio.h>
#include <stdlib.h>

#define NR 6
#define NC 20

typedef struct {
	int N, MaxN;
	rover* R;
}rList;

rList loadRovers(char* nomefile);
rover searchRover(rList L, char* rovername);
rover maxAvgQN(rList L);
void freeRList(rList* L);

#endif