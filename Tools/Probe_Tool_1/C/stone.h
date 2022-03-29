#ifndef STONE_H

#define STONE_H 1

#define MAX_N 11

typedef struct {
	char code[MAX_N];
	float qualityNumber;
	int collected;
}stone;

stone stoneCreate(char* code, float qn);

#endif