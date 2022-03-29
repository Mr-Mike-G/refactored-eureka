#ifndef RLIST_H

#define RLIST_H 1

#include "rover.h"
#include <stdio.h>
#include <stdlib.h>

#define NR 6
#define NC 20

typedef struct {
	int N;
	rover* R;
	char field[NR][NC+1];
}rList;

rList loadRList(char* roversFile, char* fieldFile);
void storeRList(rList L, char* nomefile);
void freeRList(rList* L);

#endif