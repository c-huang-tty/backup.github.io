#include <iostream>
using namespace std;
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
	/*
	function1();
	cout << globalVariable << endl;
	function2();
	cout << globalVariable << endl;
	*/

	/*
	int globalVariable = 2;
	function1();
	cout << globalVariable << endl;
	function2();
	cout << globalVariable << endl;
	*/

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