#include "rList.h"
#include <string.h>

rList loadRovers(char* nomefile) {
	FILE* fp = fopen(nomefile, "r");
	rList L;
	char name[MAX_N];
	int id, sMax;
	float qn;
	int i, j;
	fscanf(fp, "%d", &L.N);
	L.R = malloc(L.N * sizeof(rover));
	for (i = 0; i < L.N; i++) {
		fscanf(fp, "%s %d %d", name, &id, &sMax);
		L.R[i] = roverInit(name, id, sMax);
		for (j = 0; j < sMax; j++) {
			fscanf(fp, "%s %f", name, &qn);
			addStone(L.R[i], stoneCreate(name, qn));
		}
	}
	fclose(fp);
	return L;
}

void loadField(rList* L, char* nomefile) {
	FILE* fp = fopen(nomefile, "r");
	for (int i = 0; i < NR; i++) {
		fgets((*L).field[i], NC + 1, fp);
		fscanf(fp, "%*c");
	}
	fclose(fp);
}

void scanField(rList* L) {
	for (int i = 0; i < (*L).N; i++)
		for (int j = 0; j < NR; j++)
			collectStones((*L).R[i], (*L).field[j]);
}

rList loadRList(char* roversFile, char* fieldFile) {
	rList L = loadRovers(roversFile);
	loadField(&L, fieldFile);
	scanField(&L);
	return L;
}

void freeRList(rList* L) {
	for (int i = 0; i < (*L).N; i++)
		freeRover((*L).R[i]);
}

void storeRList(rList L, char* nomefile) {
	FILE* fp = fopen(nomefile, "w");
	for (int i = 0; i < L.N; i++) {
		if (i != 0) fprintf(fp, "\n");
		storeRover(L.R[i], fp);
	}
	fclose(fp);
}