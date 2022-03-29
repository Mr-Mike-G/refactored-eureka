#include "rover.h"

struct rover_t {
	char name[MAX_N];
	int id, sMax, nStones;
	float* qn;
};

rover roverInit(char* name, int id, int nS) {
	rover R = malloc(sizeof(*R));
	strcpy(R->name, name);
	R->id = id;
	R->sMax = nS;
	R->nStones = 0;
	R->qn = malloc(nS * sizeof(float));
	return R;
}

void freeRover(rover R) {
	free(R->qn);
	free(R);
}

void addQN(rover R, float qn) {
	if (R->nStones + 1 > R->sMax)
		return;
	R->qn[R->nStones] = qn;
	R->nStones++;
}

char* getRoverName(rover R) {
	return R->name;
}

int getRoverId(rover R) {
	return R->id;
}

int getNStones(rover R) {
	return R->nStones;
}

void storeStoneData(rover R, FILE* fp) {
	for (int i = 0; i < R->nStones; i++) {
		if (i == 0) fprintf(fp, "%0.2f", R->qn[i]);
		else fprintf(fp, " %0.2f", R->qn[i]);
	}
}

float getAvgQN(rover R) {
	float avg = 0;
	if (R->nStones == 0) return 0;
	for (int i = 0; i < R->nStones; i++) {
		avg += R->qn[i];
	}
	avg /= R->nStones;
	return avg;
}