## C++ Basics [04]: Function Basics

### Arguments Passing
Parameter initialization works the same way as variable initialization. If the parameter is a reference, then the parameter is bound to its argument. Otherwise, the argument’s value is copied. Some examples about passing and returning pointers and references to and from functions have been discussed in the post [Passing and Returning References and Pointers](https://c-huang-tty.github.io/2022/01/08/blog-post-title-from-file-name.html). Here I will summarize some practical aspects about argument passing mentioned in [C++ Primier (5th Edition)](https://www.oreilly.com/library/view/c-primer-fifth/9780133053043/).


#### Passing Arguments by References
__Use reference to avoid copies__

1. When it's insufficient to copy objects that are large (e.g., long `string`)
2. When objects have a type that cannot be copied (e.g., `array`)

Below is an exanple comparing the length of two strings, as the string maybe long, it's better to avoid copying them.
```cpp
// compare the length of two strings
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}
```    
    
__Use reference to return multiple variables__

There are several ways to return several values from a function, using reference is a very efficient way to do that. Below is an exanple returning the sum and difference of two integers.
```cpp
#include <iostream>
using namespace std;

void SumDiff(const int &a, const int &b, int& sum, int& diff){
    sum = a + b;
    diff = abs(a - b);
}
int main(){
    int sum, diff;
    SumDiff(3,4,sum,diff);
    cout << "sum is: " << sum << " " << "diff is: " << diff << endl;
}
```
Here is another example returning the index of the first occurrence of `c` in `s`, and the reference parameter `occurs` counts how often `c` occurs (C++ Primier, P211).
```cpp
string::size_type find_char(const string &s, char c, string::size_type &occurs){
    auto ret = s.size();    // position of the first occurrence, if any
    occurs = 0;             // set the occurrence count parameter
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i;    // remember the first occurrence of c
            ++occurs;       // increment the occurrence count
        }
    }
    return ret;             // count is returned implicitly in occurs
}
int main(){
    string::size_type occurs;
    cout << "'a' first occurs in position " << find_char("Chao Huang",'a', occurs) << endl;
    cout << "'a' ocurs " << occurs << " times" << endl;
}
```
__Use reference to const when possible__

In the above examples, `a` and `b` are defined as `const int`, `s` is defined as `const string`, what if they are defined as `int` and `string` respectively? Let's try it.

For the first example, run the following codes. 
```cpp
#include <iostream>
using namespace std;

void SumDiff(int& a, int& b, int& sum, int& diff){
    sum = a + b;
    diff = abs(a - b);
}
int main(){
    int sum, diff;
    SumDiff(3,4,sum,diff);
    cout << "sum is: " << sum << " " << "diff is: " << diff << endl;
}
```
The result is `error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'`. As `3` and `4` are `rvalues`, we cannot assign it to `lvalues` like `a` and `b`. We should call the function like below, which will print the same results.
```cpp
int a = 3, b = 4, sum, diff;
SumDiff(a,b,sum,diff);
cout << "sum is: " << sum << " " << "diff is: " << diff << endl;
```
The same issue exists with the second example.

#### Passing Arguments by Arrays
Two special properties affect how we define and use functions that operate on arrays:
1. Array cannot be copied;
2. Array is usually converted to a pointer when used.

Because of the second point, functions usually don't know the size of the array. There are several techniques to cope with it.

__Using a marker__

This method requires the array itself to contain an end marker. C-string is a good example of this.
```cpp
void print(const char* p){
    if(p)
        while(p)
            cout << *p++ << " ";
        cout << endl;
}
```

__Using standard library conventions__

This method is to pass pointers to the first and last element in the array. We can realize this using `begin` and `end` functions. 
```cpp
void print(const int* beginP, const int* endP){
    while(beginP != endP){
        cout << *beginP++ << " ";
    }
    cout << endl;
}
```

__Explicitly passing size of the array__
```cpp
void print(const int intArr[], size_t size){
    for(size_t i = 0; i < size; i++){
        cout << intArr[i] << " ";
    }
    cout << endl;
}
```

__Array Reference Parameters__

We can also define a parameter that is a reference to an array, as the size of an array is part of its type, we can print out the elements using __range `for`__ statement. However, the fact that the size is part of the type limits the usefulness of this version of 'print'. (This may not be the case using `templates`)
```cpp
void print(int (&intArr)[10]){
    for(auto elem: intArr)
        cout << elem << " ";
    cout << endl;
}
```
For multidimentional array, the same method applies.
```cpp
void print(int (&intArr)[10][10]){
    for (auto &row : intArr){  
        for (auto &col : row)  
            cout << col << " ";        
        cout << endl;
    }
}
```
Except this, the multidimensional array can also be passed in the following two ways.
```cpp
void print(int (*intArr)[10], int rowSize){

}
```
```cpp
void print(int intArr[][10], int rowSize){

}
```

### Return Statement

#### Return a Reference or Pointer to a Local Object is Not Allowed
The return value is used to initialize a temporary at the call site, and that temporary is the result of the function call. When a function completes, its storage is freed, this means that references to local objects refer to memory that is no longer valid. The reference or pointer would point to a nonexistent object. 

One good way to ensure that the return is safe is to ask: __To what preexisting object is the reference referring?__

#### Return Class Types
If a function returns a pointer, reference or object of class type, we can use the result of a call to call a member of the resulting object. This means that we can return multiple values from a function by defining a `class` or `structure` by including those values we want to return.

In the example below, function `Add` take two struct type variables as arguments and return a struct type object to store the total number of the books with the same ISBN. In the `main` function, we can use `Add(book1, book2).number` to get the member of the returned object directly.   
```cpp
struct Book {
    string ISBN;
    int    number;
};

Book Add(Book book1, Book book2) {
    Book totalBook;
    if (book1.ISBN == book2.ISBN) {
        totalBook.ISBN = book1.ISBN; // or book2.ISBN
        totalBook.number = book1.number + book2.number;
        return totalBook;
    }
    else {
        throw invalid_argument("The books have different ISBN numbers!");
    }
}
int main() {
    Book book1,book2;
    book1.ISBN = "book";
    book1.number = 3;
    book2.ISBN = "book";
    book2.number = 4;
    cout << Add(book1, book2).number << endl;
}
```

#### Reference Returns Are Lvalues
Whether a function call is an lvalue depends on the return type of the function. As the example given in the post [Rvalue and Rvalue References](https://c-huang-tty.github.io/2022/01/09/blog-post-title-from-file-name.html), calls to functions that return references are lvalues. And a call to a function that returns a reference can be used in the same ways as any other lvalue.

In the following example, `function(localVariable)` can be used as an `lvalue` and `*ptr` before and after the function call would be `0` and `1` respectively.
```cpp
int globalVariable = 1;
int& function(int& localVariable){
    return localVariable;
}
int main(){
    int localVariable = 0;
    int* ptr = &localVariable;
    cout << *ptr << endl;
    function(localVariable) = globalVariable;
    cout << *ptr << endl;
}
```

#### Return a Pointer to an Array
Because we cannot copy an array, a function cannot return an array. However, a function can return a pointer or a reference to an array. 

The form of a function that returns a pointer to an array is:
>Type (*function(parameter_list))[dimension]

Notice that for a onw dimensional array, the form would simply be:
>Type *function(parameter_list)

Below is an example showing the difference between returning a pointer to one and two dimensional arrays, `*ptr1` and `*ptr2` would be `1` and `5` respectively. 
```cpp
int arr1[5] = { 1,2,3,4,5 };
int arr2[2][3] = { 5,4,3,2,1,0 };
int* function1() {
    return arr1;
}
int(*function2())[3]{
    return arr2;
}
int main() {
    int* ptr1;
    int (*ptr2)[3];
    ptr1 = function1();
    ptr2 = function2();
    cout << *ptr1 << endl;
    cout << **ptr2 << endl;
}
```

The most straight way is to use a type alias, for the example above, the codes below would also work. , `*ptr3` and `*ptr4` would be `2` and `1` respectively. 
```cpp
int arr2[2][3] = { 5,4,3,2,1,0 };
typedef int arr3[3];
using arr4 = int[3];
arr3* function3(){
    return arr2;
}
arr4* function4(){
    return arr2;
}
int main() {
    int (*ptr3)[3], (*ptr4)[3];
    ptr3 = function2();
    ptr4 = function2();
    cout << *(*(ptr3 + 1)) << endl;
    cout << *(*(ptr3 + 1) + 1) << endl;
}
```

The same function can also be realized using so-called __trailing return type__, for the example above, this will also work. `*ptr5` would be `0`.
```cpp
auto function5() -> int(*)[3]{
    return arr2;
}
int main() {
    int (*ptr5)[3];
    ptr5 = function2();
    cout << *(*(ptr5 + 1) + 2) << endl;
}
```

