#include "IncDec.h"
/*
int globalVariable = 0;

void function1() {
	globalVariable += 1;
}

void function2() {
	globalVariable -= 1;
}
*/
globalData globalVariableStruct;

void function1() {
	globalVariableStruct.data1 += 1;
}

void function2() {
	globalVariableStruct.data2 -= 1;
}