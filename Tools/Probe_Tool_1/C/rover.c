#include "rover.h"

struct rover_t {
	char name[MAX_N];
	int id, sMax, nStones;
	stone* stones;
};

rover roverInit(char* name, int id, int nS) {
	rover R = malloc(sizeof(*R));
	strcpy(R->name, name);
	R->id = id;
	R->sMax= nS;
	R->nStones = 0;
	R->stones = malloc(R->sMax * sizeof(stone));
	return R;
}

void freeRover(rover R) {
	free(R->stones);
	free(R);
}

int checkStone(rover R, stone s) {
	for (int i = 0; i < R->nStones; i++) {
		if (!strcmp(R->stones[i].code, s.code))
			return 1;
	}
	return 0;
}

void addStone(rover R, stone s) {
	if (R->nStones + 1 > R->sMax)
		return;
	if (checkStone(R, s)) return;
	R->stones[R->nStones] = s;
	R->nStones++;
}

int nStonesCollected(rover R) {
	int n = 0;
	for (int i = 0; i < R->nStones; i++)
		n += R->stones[i].collected;
	return n;
}

void storeRover(rover R, FILE* fp) {
	int s = nStonesCollected(R);
	fprintf(fp, "%s %d %d", R->name, R->id, s);
	for (int i = 0; i < R->nStones; i++) {
		if (R->stones[i].collected > 0) {
			for (int j = 0; j < R->stones[i].collected; j++) {
				if (i == 0 && j==0) fprintf(fp, "\n%0.2f", R->stones[i].qualityNumber);
				else fprintf(fp, " %0.2f", R->stones[i].qualityNumber);
			}
		}
	}
}

void collectStones(rover R, char* string) {
	char* c;
	int l1, l2;
	for (int i = 0; i < R->nStones; i++) {
		c = string;
		l1 = strlen(c);
		l2 = strlen(R->stones[i].code);
		while (c != NULL && l1 - l2 > 0) {
			if ((c = strstr(c, R->stones[i].code)) != NULL) {
				R->stones[i].collected++;
				c += l2;
				l1 = strlen(c);
			}
		}
	}
}