## Inline and Constexpr Functions

Defining a function makes the code easier to read and understand. However, one potential drawback to make a function is that calling a function is apt to be slower than evaluating the equivalent expressions. On most machines, a function call does a lot of work:
- Registers are saved before the call and restored after the return;
- Arguments may be copied;
- The program branches to a new location.

`inline` and `constexpr` functions are introduced to boost the efficiency of the programs.

### inline Functions
As the name suggested, a function specified as `inline` is expanded "in line" at each call. We can define an inline function by putting the keyword `inline` before the function's return type. Here is an example, when `cout << Sum(3, 4) << endl;` is excuted, it (probably) would be expanded during compilation into something like `cout << 3 + 4 << endl;`.
```cpp
int Sum(const int& a, const int& b) {
    return a + b;
}
int main(){
    cout << Sum(3, 4) << endl;
}
```

It is to be noted that the inline mechanism is meant to optimize small, straight-line functions that are called frequently. The compiler may choose to ignore this request.

### constexpr Functions
A `constexpr` function can be defined by putting the keyword `constexpr` before the function's return type. When a `constexpr` function is defined, the compiler will replace a call to it with its resulting value, which will boost efficiency. However, it has some restrictions:
- The return type and the type of each parameter in a must be a literal type;
- The function body must contain exactly one return statement.

It is to be noted that a `constexpr` function is not required to return a constant expression. If we call a `constexpr` function with an expression that is not a constant expression, then the return is not a constant expression. Here I modified the above example a bit, we would see that although `Sum(a, b)` can be excuted, `int arr2[Sum(a, b)];` would issue an error, as the result of `Sum(a, b)` would be a non-const expression, which would not be accepted by `int arr2[]`.
```cpp
constexpr int Sum(const int& a, const int& b) {
    return a + b;
}
int main(){
    int a = 3, b = 4;
    cout << Sum(3, 4) << endl;  // 7
    cout << Sum(a, b) << endl;  // 7
    int arr1[Sum(3, 4)];        // ok
    int arr2[Sum(a, b)];        // error
}
```
To eliminate the error, we can use dynamic array, which will be summarized later, here is a simple example.
```cpp
int main(){
    int a = 3, b = 4;
    int* arr2 = new int[Sum(a, b)]; 
    delete[] arr2;
    arr2 = nullptr;
}
```

### constexpr Expressions
A constant expression is an expression whose value cannot change and that can be evaluated at compile time. A `literal` is a constant expression. A const object that is initialized from a constant expression is also a constant expression. 

Whether a given object (or expression) is a constant expression depends on the types and the initializers.
```cpp
const int max_files = 20;           // max_files is a constant expression
const int limit = max_files + 1;    // limit is a constant expression
int staff_size = 27;                // staff_size is not a constant expression
const int sz = get_size();          // sz is not a constant expression
```

It is important to understand that when we define a pointer in a `constexpr` declaration, the `constexpr` specifier applies to the pointer, not the type to which the pointer points:
```cpp
const int *p = nullptr;         // p is a pointer to a const int
constexpr int *q = nullptr;     // q is a const pointer to int
```
