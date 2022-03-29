#ifndef ROVER_H

#define ROVER_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stone.h"

typedef struct rover_t* rover;

rover roverInit(char* name, int id, int nS);
void freeRover(rover R);
void addStone(rover R, stone s);
void storeRover(rover R, FILE* fp);
void collectStones(rover R, char* string);

#endif