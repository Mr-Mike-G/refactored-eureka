#include "rList.h"
#include <string.h>

rList loadRovers(char* nomefile) {
	FILE* fp = fopen(nomefile, "r");
	rList L;
	L.MaxN = 5;
	L.N = 0;
	char name[MAX_N];
	int id, sMax;
	float qn;
	L.R = malloc(L.MaxN * sizeof(rover));
	while(fscanf(fp, "%s %d %d", name, &id, &sMax)==3) {
		if (L.N + 1 > L.MaxN) {
			L.MaxN = L.MaxN + (L.MaxN / 2);
			L.R=realloc(L.R, L.MaxN * sizeof(rover));
		}
		L.R[L.N] = roverInit(name, id, sMax);
		for (int j = 0; j < sMax; j++) {
			fscanf(fp, "%f", &qn);
			addQN(L.R[L.N], qn);
		}
		L.N++;
	}
	fclose(fp);
	return L;
}

void freeRList(rList* L) {
	for (int i = 0; i < (*L).N; i++)
		freeRover((*L).R[i]);
}

rover searchRover(rList L, char* rovername) {
	for (int i = 0; i < L.N; i++) {
		if (!strcmp(rovername, getRoverName(L.R[i])))
			return L.R[i];
	}
	return NULL;
}

rover maxAvgQN(rList L) {
	float avgMax = -1, avg;
	rover R = NULL;
	for (int i = 0; i < L.N; i++) {
		avg = getAvgQN(L.R[i]);
		if (avg > avgMax) {
			avgMax = avg;
			R = L.R[i];
		}
	}
	return R;
}