## Data Sharing [C++] [02]: Between Multiple Files

Code in this post can be found in this folder [DataSharingBetweenFiles](https://github.com/c-huang-tty/c-huang-tty.github.io/tree/main/code/cpp/DataSharing/DataSharingBetweenFiles)

### extern
To share data between different files within a project, the most common way to apply the `extern` declaration to global variables. 

The best pratctice is to define the global variables in source files and then use a header file to declare those global variables by `extern`. This can be demonstrated by `IncDec.h`, `IncDec.cpp` and main file `DataSharingBetweenFiles.cpp`.

```cpp
// IncDec.h
#pragma once

extern int globalVariable;

void function1();
void function2();
```
```cpp
// IncDec.cpp
#include "IncDec.h"

int globalVariable = 0;

void function1() {
    globalVariable += 1;
}

void function2() {
    globalVariable -= 1;
}
```
```cpp
// DataSharingBetweenFiles.cpp
#include <iostream>
#include "IncDec.h"
using namespace std;

int main() {
    function1();
    cout << globalVariable << endl; // 1
    function2();
    cout << globalVariable << endl; // 0
}
```

Alternatively, We can also define the global variables in the main file. However, it would be hard to read when we have dozens of files, with each containing a couple of global variables. Therefore, it is not recommended to define global variables in the main source file. 

---
### struct/class
The better alternative to global bariables is to define a **struct/class** in the header file. This can be demonstrated by `IncDec.h`, `IncDec.cpp` and main file `DataSharingBetweenFiles.cpp` modified from the above example.

```cpp
// IncDec.h
#pragma once
struct globalData {
    int data1 = 0;
    int data2 = 0;
};

extern globalData globalVariableStruct;

void function1();
void function2();
```
```cpp
// IncDec.cpp
#include "IncDec.h"

globalData globalVariableStruct;

void function1() {
    globalVariableStruct.data1 += 1;
}

void function2() {
    globalVariableStruct.data2 -= 1;
}
```
```cpp
// DataSharingBetweenFiles.cpp
#include <iostream>
#include "IncDec.h"
using namespace std;

int main() {
    function1();
    cout << globalVariableStruct.data1 << endl; // 1
    function2();
    cout << globalVariableStruct.data2 << endl; // -1
}
```

`struct` is especially useful when a group of variables are related. For example, in order to define dynamics of a vehicle, we don't need to define dozens of global variables one by one. Instead, we can define a `struct` named `vehicleDynamics`, and then include all the variables that we concern into the `struct`. It is also very flexible in that we don't need to change our code much if we want to add more variables into the structure later.

---
