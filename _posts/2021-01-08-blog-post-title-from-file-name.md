## C++ Basics [02]: Passing and Returning References and Pointers

Codes in this post can be found in [PassingReferencePointer.cpp](https://github.com/c-huang-tty/c-huang-tty.github.io/blob/main/code/cpp/ReferencePointer/PassingReferencePointer.cpp) and [ReturningReferencePointer.cpp](https://github.com/c-huang-tty/c-huang-tty.github.io/blob/main/code/cpp/ReferencePointer/ReturningReferencePointer.cpp).

### Passing Pointers to a Function
If a pointer is passed to a function as a parameter and tried to be modified, we will find that the value of the pointer doesn't change outside of the function. This is because only a copy of the pointer is passed to the function. This is similar to any other objects like `int`. When we pass a `int` as a parameter to a function, its value outside of the function won't be changed, as its scope is within that function. `*ptr` before and after the function call would be `1` and `1` respectively. 
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
    cout << val << endl;
    return 0;
}
```

---
### Passing References to a Function
If a reference is passed to a function as a parameter and tried to be modified, we will find that the value of the reference outside of the function will also be changed. This is because the address of the variable is passed to the function. `*ptr` before and after the function call would be `1` and `0` respectively. 
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
   cout << val << endl;
   return 0;
}
```

---
### Passing Pointers to Pointers to a Function
In order to modify the value of the pointer outside of the function using a pointer as a parameter of the function, we can pass the address of the pointer to the function as a parameter. This can be realized by passing `pointer to pointer` as a parameter of the function, which is shown in the below codes. `*ptr` before and after the function call would be `1` and `0` respectively.
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
    cout << val << endl;
    return 0;
}
```
Notice that this is different from the following codes, which modify the object it points to (`val`), not the pointer (`ptr`) itself. In the above codes, `val` will still be `1` in the end; whereas in the codes below, `val` will become `0`. 
```cpp
#include <iostream>
using namespace std;

int globalVariable = 0;

void function(int* ptr) {
    *ptr = globalVariable;
}
int main() {
    int val = 1;
    int* ptr = &val;
    cout << *ptr << endl;
    function(ptr);
    cout << *ptr << endl;
    cout << val << endl;
    return 0;
}
```

---
### Passing References to Pointers to a Function 
As a reference allows the called function to modify a local variable of the caller function, we can also get the above results by passing `reference to pointer` as a parameter of the function. `*ptr` before and after the function call would be `1` and `0` respectively. 
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
    cout << val << endl;
    return 0;
}
```

---
---
Alternatively, we can also get the same results by returning `pointers` or `references` from a function. `*ptr` before and after the function call would be `1` and `0` respectively. 
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
    cout << val << endl;
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
    cout << val << endl;
    return 0;
}
```


---
