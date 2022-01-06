## C++ Basics [01]: References & Pointers

### References
A reference is not an object. Instead, it defines an alternative name for an object. When we define a reference, instead of copying the initializer's value, we **bind** the reference to its initialiizer. A reference is defined by writing a declarator of the form `&ref`, where `ref` is the name being declared.
```cpp
int refVal = 1;
int &ref = refVal;
ref = 2; // same as refVal = 2
```
Notes  

- As a reference is not an object, we can't define a reference to a reference.
- The type of a reference and the object to which it refers to must be the same.
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
- The type of a pointer and the object to which it points to must be the same.

---
### `&` and `*`
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
