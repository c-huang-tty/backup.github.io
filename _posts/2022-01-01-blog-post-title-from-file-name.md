## Data Sharing [C++] [01]: Between Functions Within A File

Codes in this post can be found in [DataSharingBetweenFunctions.cpp](https://github.com/c-huang-tty/c-huang-tty.github.io/blob/main/code/cpp/DataSharing/DataSharingBetweenFunctions.cpp?ts=4).

### global variable
The simplest way to share data between different functions within a file is to simply define __global variables__ on top of the program.

For example, if I define a global variable named `globalVariable` and two functions named `funtion1` and `function2` and call them in the `main` function, the `cout` result would be `1` and `0` respectively. 
```cpp
int globalVariable = 0;

void function1() {
    globalVariable += 1;
}

void function2() {
    globalVariable -= 1;
}
```
```cpp
int main() {
    function1();
    cout << globalVariable << endl;
    function2();
    cout << globalVariable << endl;
    system("pause > 0");
}
```

However, there is a problem here. When I define a __local variable__ with the same name as the __global variable__, the __global variable__ will be overridden by the __local variable__. For example, if I define the `globalVariable` again in the `main` function and then call `funtion1` and `function2`, the `cout` result would be `2` and `2` respectively. 
```cpp
int main () {
    int globalVariable = 2;
    function1();
    cout << globalVariable << endl;
    function2();
    cout << globalVariable << endl;
    system("pause > 0");
}
```
To solve this problem, two simple methods are available. We can either define a `namespace` to include the global variable, or we can shadow the local variable using `extern` declaration.

---
### namespace
Here I defined a `namespace` named `g`, again, the `cout` result would be `1` and `0` respectively.
```cpp
namespace g{
    int globalVariable = 0;
}

void function1() {
    g::globalVariable += 1;
}

void function2() {
    g::globalVariable -= 1;
}
```
```cpp
int main() {
    int globalVariable = 2;
    function1();
    cout << g::globalVariable << endl;
    function2();
    cout << g::globalVariable << endl;
    system("pause > 0");
}
```

---
### extern
Here I used the `extern` declaration before call `funtion1` and `function2`, again, the `cout` result would be `1` and `0` respectively. (`{` and `}` are necessary, which define the scope of the variable.)
```cpp
int globalVariable = 0;

void function1() {
    globalVariable += 1;
}

void function2() {
    globalVariable -= 1;
}
```
```cpp
int main() {
    int globalVariable = 2;	
    {
        extern int globalVariable;
        function1();
        cout << globalVariable << endl; 	
        function2();
        cout << globalVariable << endl;
    }
    return 0;
}
```

---
### static
`static` can be very useful when we have to define a variable within a `while` loop and don't want to create and destroy it each time it comes into and goes out of scope, so that we can maintain its value between function calls. Here is a simple example, using `stepCount`, it's easy to control which part of athe code to execute. Again, the `cout` result would be `1` and `0` respectively.   
```cpp
int main() {
    while(1) {
        static int stepCount = 0; 
        if (stepCount == 0){
            function1();
            cout << globalVariable << endl;
            stepCount++;
        }else if (stepCount = 1){
            function2();
            cout << globalVariable << endl;
            stepCount++;
        }else{
            break;
        }
   }  
   return 0;
}
```
Another usage of `static` is to define the static variable within a function. The variable is initialized before the first time execution, it is not destroyed when a function ends, instead it is destroyed when the program terminates. Below is a simple example, the `cout` result would be `0` and `1` respectively.   
```cpp
int function() {
    static int stepCount = 0;
    return stepCount++;
}
int main(){
    cout << function() << endl;
    cout << function() << endl;
}

```

---
[//]: <> (Due to a plugin called `jekyll-titles-from-headings` which is supported by GitHub Pages by default. The above header (in the markdown file) will be automatically used as the pages title.)


