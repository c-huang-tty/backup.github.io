#pragma once
//extern int globalVariable;
#ifndef INCDEC_H
#define INCDEC_H
/*
extern int globalVariable;
*/
struct globalData {
	int data1 = 0;
	int data2 = 0;
};

extern globalData globalVariableStruct;

void function1();
void function2();

#endif