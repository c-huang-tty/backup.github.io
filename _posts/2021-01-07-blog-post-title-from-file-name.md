## C++ Basics [01]: References and Pointers Basics

### References
A reference is not an object. Instead, it defines an alternative name for an object. When we define a reference, instead of copying the initializer's value, we **bind** the reference to its initialiizer. A reference is defined by writing a declarator of the form `&ref`, where `ref` is the name being declared.
```cpp
int refVal = 1;
int &ref = refVal;
ref = 2; // same as refVal = 2
```
Notes  

- As a reference is not an object, we can't define a reference to a reference.
- The type of a reference and the object to which it refers to must be the same (__except__ references to const and classes related by interitance).
- A reference may be bound only to an object, not to a literal or to the result of a more general expression.

---
### Pointers
A pointer is an object, and it need not to be initialized at the time it is defined. A pointer is defined by writing a declarator of the form `*ptr`, where `ptr` is the name being declared. A pointer holds the address of another object. We get the address of an object by using the address-of operator `&` and use the dereference operator `*` to access that object.
```cpp
int ptrVal = 1;
int *ptr = &ptrVal;
```
Notes  

- As a reference is not an object, we can't define a pointer to a reference.
- The type of a pointer and the object to which it points to must be the same (__except__ pointers to const and classes related by interitance).

---
### & and *
```cpp
int i  = 1;
int &r = i;   // & follows a type and is part of a declaration; r is a reference
int *p;       // * follows a type and is part of a declaration; p is a pointer
 p = &i;      // & is used in an expression as the address-of operator
*p = i;       // * is used in an expression as the dereference operator
```

---
### NULL Pointers & Void Pointers
A **null pointer** does not point to any object. Code can check whether a pointer is null before attempting to use it.
```cpp
int *p1 = nullptr; // suggested
int *p2 = 0;
int *p3 = NULL;
```

The type `void*` is a special pointer type that can hold the address of any object.
```cpp
double obj = 3.14, *pd = &obj;
void *pv = &obj; // obj can be an object of any type
```

---
### Pointers to Pointers
As pointer is an object, we can also define a pointer to a pointer as `**`, and a pointer to a pointer to a pointer as `***`, and so on. 
```cpp
int valPtr = 1;
int *pi = &valPtr;   // pi points to an int
int **ppi = &pi;     // ppi points to a pointer to an int
```
To access the underlying object, just dereference the same number of times. In the following, `valPtr`, `*pi`, `**ppi` would be the same.
```cpp
cout << "The value of valPtr: " << valPtr << endl
     << "The indirect value: " << *pi << endl
     << "The doubly indirect value: " << **ppi << endl;
```

---
### References to Pointers
A reference is not an object. Hence, we may not have a pointer to a reference. However, because a pointer is an object, we can define a reference to a pointer.
```cpp
int i = 1;
int *p;       // p is a pointer to int
int *&r = p;  // r is a reference to the pointer p
 r = &i;      // r refers to a pointer; assigning &i to r makes p point to i
*r = 0;       // dereferencing r yields i, the object to which p points; changes i to 0
```
The symbol closest to the name of the variable (in this case the `&` in `&r`) is the one that has the most immediate effect on the variable’s type. Thus, we know that `r` is a reference. The rest of the declarator determines the type to which r refers. The next symbol, `*` in this case, says that the type `r` refers to is a pointer type. Finally, the base type of the declaration says that `r` is a reference to a pointer to an `int`.

---
---
### References to Const
__Reference to `const`__ is a reference that refers to a const, which cannot be used to change the object to which the reference is bound. However, it says nothing about whether the underlying object itself is const.
```cpp
int i = 1;
int &r1 = i;       // r1 bound to i
const int &r2 = i; // r2 also bound to i; but cannot be used to change i
r1 = 0;            // r1 is not const; i is now 0
r2 = 0;            // error: r2 is a reference to const
```


---
### Pointers to Const
Like __Reference to `const`__, __pointer to `const`__ is a pointer that refers to a const, which cannot be used to change the object to which the pointer points. It also says nothing about whether the underlying object itself is const.
```cpp
const double pi = 3.14;   // pi is const; its value may not be changed
double *ptr = &pi;        // error: ptr is a plain pointer
const double *cptr = &pi; // ok: cptr may point to a double that is const
*cptr = 42;               // error: cannot assign to *cptr

double dval = 3.14;       // dval is a double; its value can be changed
cptr = &dval;             // ok: but can’t change dval through cptr
```

--- 
### Const Pointers
Like any other const object, a const pointer must be initialized, and once initialized, its value (i.e., the address that it holds) may not be changed.
```cpp
int errNumb = 0;
int *const curErr = &errNumb;  // curErr will always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi; // pip is a const pointer to a const object
```
Again, a pointer is itself const says nothing about whether we can use the pointer to change the underlying object. Whether we can change that object depends entirely on the type to which the pointer points.
```cpp
int i = 1;
int *const p1 = &i;
*p1 = 2;   // ok
```

---
---
### Pointers and Arrays
`Pointers` to an `array` are like `iterators` to an `vector`. When we define a pointer to an array, we are really using a pointer to the first element in that array.
```cpp
string str[]  = {"Chao", "Huang"};
string *ptr = num;    // equivalent to p2 = &str[0]
```
`C++ 11` includes two functions `begin` and `end` in header file `iterator` that behave like iterators. `begin` returns a pointer to the first, and `end` returns a pointer one past the last element in the given array.
```cpp
int ia[] = {0,1,2,3,4,5,6,7,8,9}; // ia is an array of ten ints
int *beg = begin(ia);             // pointer to the first element in ia
int *last = end(ia);              // pointer one past the last element in ia
```
 Multidimensional array is a little different. Because a multidimensional array is really an array of arrays, the pointer type to which the array converts is a pointer to the first inner array. 
 ```cpp
 int ia[3][3] = {1,2,3,4,5,6,7,8,9};
 int *p = ia;      // error: cannot convert ‘int (*)[3]’ to ‘int*’ in initialization
 int (*p)[3] = ia; // p points to an array of 3 ints
 cout << **p;      // this will print out 1
 p = &ia[2];       // p points now to the last row of ia
 cout << **p;      // this will print out 7
 ```
 However, we can also use `auto` to simplify the initialization. 
 ```cpp
 int ia[3][3] = {1,2,3,4,5,6,7,8,9};
 auto p = ia;  // p points to an array of 3 ints
 cout<< **p;   // this will print out 1
 ```
 
---
