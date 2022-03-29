#include <stdio.h>
#include <stdlib.h>
#include "rover.h"
#include "rList.h"

int main() {
	rList L = loadRList("rovers.txt", "field.txt");
	storeRList(L, "output.txt");
	freeRList(&L);
	return 0;
}