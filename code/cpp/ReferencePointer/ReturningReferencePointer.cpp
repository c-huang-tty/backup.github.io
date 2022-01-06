#include <iostream>
using namespace std;

int globalVariable = 0;

/* Returning reference from function */
int& function() {
	return globalVariable;
}
int main() {
	int val = 1;
	int* ptr = &val;
	cout << *ptr << endl;
	ptr = &function();
	cout << *ptr << endl;
	return 0;
}
