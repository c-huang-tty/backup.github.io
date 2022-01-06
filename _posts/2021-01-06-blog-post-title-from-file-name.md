## Data Sharing [C++] [02]: Between Multiple Files

Code in this post can be found in this folder [DataSharingBetweenFiles](https://github.com/c-huang-tty/c-huang-tty.github.io/tree/main/code/cpp/DataSharing/DataSharingBetweenFiles)

### extern
To share data between different files within a project, the most common way to use the `extern` declaration. 

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
    cout << globalVariable << endl;
    function2();
    cout << globalVariable << endl;
}
```

Alternatively, We can also define the global variables in the main file. However, it would be hard to read when we have dozens of files, with each containing a couple of global variables. Therefore, it is not recommended to define global variables in the main source file. 
