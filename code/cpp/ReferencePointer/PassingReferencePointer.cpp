#include <iostream>
using namespace std;

int globalVariable = 0;

/* pass pointer to function */
/*
void function(int* ptr) {
	ptr = &globalVariable;
}
int main() {
	int val = 1;
	int* ptr = &val;
	cout << *ptr << endl;
	function(ptr);
	cout << *ptr << endl;
	return 0;
}
*/

/* passing reference to function */
/*
void function(int& ptr) {
	ptr = globalVariable;
}
int main() {
	int val = 1;
	int& ptr = val;
	cout << ptr << endl;
	function(ptr);
	cout << ptr << endl;
	return 0;
}
*/

/* passing pointer to pointer to function */
/*
void function(int** ptr) {
	*ptr = &globalVariable;
}
int main() {
	int val = 1;
	int* ptr = &val;
	cout << *ptr << endl;
	function(&ptr);
	cout << *ptr << endl;
	return 0;
}
*/

/* passing reference to pointer to function */
void function(int*& ptr) {
	ptr = &globalVariable;
}
int main() {
	int val = 1;
	int* ptr = &val;
	cout << *ptr << endl;
	function(ptr);
	cout << *ptr << endl;
  return 0;
}
