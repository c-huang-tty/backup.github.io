#include <iostream>
using namespace std;
/* using namespace to define global variable */
/*
namespace g{
	int globalVariable = 0;
}
void function1() {
	g::globalVariable += 1;
}

void function2() {
	g::globalVariable -= 1;
}
*/

int globalVariable = 0;

void function1() {
	globalVariable += 1;
}

void function2() {
	globalVariable -= 1;
}

int main() {
	/* using global variable */
	/*
	function1();
	cout << globalVariable << endl;
	function2();
	cout << globalVariable << endl;
	*/

	/* global variable overriden by local variable */
	/*
	int globalVariable = 2;
	function1();
	cout << globalVariable << endl;
	function2();
	cout << globalVariable << endl;
	*/

	/* using extern to shadow local variable */
	/*
	int globalVariable = 2;
	{
		extern int globalVariable;
		function1();
		cout << globalVariable << endl;

		function2();
		cout << globalVariable << endl;
	}
	*/

	/* using namespace */
	/*
	int globalVariable = 2;
	function1();
	cout << g::globalVariable << endl;
	function2();
	cout << g::globalVariable << endl;
	*/
	
	/* usage of static variable */
	while (1) {
		static int stepCount = 0;
		if (stepCount == 0) {
			function1();
			cout << globalVariable << endl;
			stepCount++;
		}
		else if (stepCount == 1) {
			function2();
			cout << globalVariable << endl;
			stepCount++;
		}
		else {
			break;
		}
	}
	return 0;
}
