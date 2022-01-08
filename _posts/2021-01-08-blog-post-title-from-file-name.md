## C++ Basics [02]: Passing/Returning References and Pointers

Codes in this post can be found in [PassingReferencePointer.cpp](https://github.com/c-huang-tty/c-huang-tty.github.io/blob/main/code/cpp/ReferencePointer/PassingReferencePointer.cpp) and [ReturningReferencePointer.cpp](https://github.com/c-huang-tty/c-huang-tty.github.io/blob/main/code/cpp/ReferencePointer/ReturningReferencePointer.cpp).

### Passing Pointers to a Function
If a pointer is passed to a function as a parameter and tried to be modified, we will find that the value of the pointer doesn't change outside of the function. This is because only a copy of the pointer is passed to the function. This is similar to any other objects like `int`. When we pass a `int` as a parameter to a function, its value outside of the function won't be changed, as its scope is within that function. The `cout` results of the following codes would be `1` and `1` respectively. 
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

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
```

---
### Passing References to a Function
If a reference is passed to a function as a parameter and tried to be modified, we will find that the value of the reference outside of the function will also be changed. This is because the address of the variable is passed to the function. The `cout` results of the following codes would be `1` and `0` respectively. 
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

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
```

---
### Passing Pointers to Pointers to a Function
In order to modify the value of the pointer outside of the function using a pointer as a parameter of the function, we can pass the address of the pointer to the function as a parameter. This can be realized by passing `pointer to pointer` as a parameter of the function, which is shown in the below codes. The `cout` results would be `1` and `0` respectively.
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

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
```

---
### Passing References to Pointers to a Function 
As a reference allows the called function to modify a local variable of the caller function, we can also get the above results by passing `reference to pointer` as a parameter of the function. The `cout` results of the following codes would be `1` and `0` respectively. 
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

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
```

---
---
Alternatively, we can also get the same results by returning `pointers` or `references` from a function. The `cout` results of both of the following codes would be `1` and `0` respectively. 
### Returning Pointers From a Function
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

int* function() {
    return &globalVariable;
}
int main() {
    int val = 1;
    int* ptr = &val;
    cout << *ptr << endl;
    ptr = function();
    cout << *ptr << endl;
    return 0;
}
```

---
### Returning References From a Function
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

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
```


---
