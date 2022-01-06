#include <iostream>
#include "IncDec.h"
using namespace std;
/*
int main() {
	function1();
	cout << globalVariable << endl;
	function2();
	cout << globalVariable << endl;
}
*/
int main() {
	function1();
	cout << globalVariableStruct.data1 << endl;
	function2();
	cout << globalVariableStruct.data2 << endl;
}
