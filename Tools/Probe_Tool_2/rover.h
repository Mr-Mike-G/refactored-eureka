#ifndef ROVER_H

#define ROVER_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N 10

typedef struct rover_t* rover;

rover roverInit(char* name, int id, int nS);
void freeRover(rover R);
void addQN(rover R, float qn);
char* getRoverName(rover R);
int getRoverId(rover R);
int getNStones(rover R);
float getAvgQN(rover R);
void storeStoneData(rover R, FILE* fp);

#endif