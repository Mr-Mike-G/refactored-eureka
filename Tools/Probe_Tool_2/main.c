#include <stdio.h>
#include <stdlib.h>
#include "rover.h"
#include "rList.h"

typedef enum { p_rovers, p_rover, avg_qn, stop, err } command;

command readCommand(char* c);

int main() {
	rList L = loadRovers("output.txt");
	char com[10 + MAX_N], word[9];
	command c;
	rover R = NULL;
	fprintf(stdout, "Commands:\n");
	fprintf(stdout, "- p_rovers : prints-out the number of rovers, their names, identifiers, and number of stones collected\n"
		"- p_rover <rover_name>: given a rover name, prints-out its identifier, and all stone datas\n"
		"- avg_qn : prints-out the name, identifier, all stone datas and the average stone quality for the rover whose average stone quality is bigger\n"
		"- stop : end the program\n");
	do {
		fprintf(stdout, "\nType a command: ");
		fgets(com, 10 + MAX_N, stdin);
		sscanf(com, "%s", word);
		c = readCommand(word);
		switch (c)
		{
		case p_rovers:
			fprintf(stdout, "%d rovers\n", L.N);
			for (int i = 0; i < L.N; i++)
				fprintf(stdout, "-%s\tId=%d\nStones collected=%d\n\n", getRoverName(L.R[i]), getRoverId(L.R[i]), getNStones(L.R[i]));
			break;
		case p_rover:
			sscanf(com, "%*s %s", com);
			R = searchRover(L, com);
			if (R == NULL) fprintf(stderr, "Rover not found\n");
			else {
				fprintf(stdout, "Id=%d\nStones collected=%d\nQuality numbers: ", getRoverId(R), getNStones(R));
				storeStoneData(R, stdout);
				fprintf(stdout, "\n");
			}
			break;
		case avg_qn:
			R = maxAvgQN(L);
			if (R == NULL) fprintf(stderr, "Rover not found\n");
			else {
				fprintf(stdout, "%s\tId=%d\nStones collected=%d\nQuality numbers: ", getRoverName(R), getRoverId(R), getNStones(R));
				storeStoneData(R, stdout);
				fprintf(stdout, "\nAverage stone quality=%0.2f\n", getAvgQN(R));
			}
			break;
		case stop:
			fprintf(stdout, "Closing the program\n");
			break;
		case err:
			fprintf(stderr, "Invalid command\n");
			break;
		}
	} while (c != stop);

	freeRList(&L);
	return 0;
}

command readCommand(char* c) {
	char tab[err][9] = { "p_rovers","p_rover","avg_qn","stop" };
	int i;
	_strlwr(c);
	for (i = 0; i < err && strcmp(c, tab[i]); i++);
	return i;
}