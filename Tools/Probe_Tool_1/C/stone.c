#include "stone.h"
#include <string.h>

stone stoneCreate(char* code, float qn) {
	stone s;
	strcpy(s.code, code);
	s.qualityNumber = qn;
	s.collected = 0;
	return s;
}