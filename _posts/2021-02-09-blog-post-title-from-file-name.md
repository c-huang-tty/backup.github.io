## C++ Basics [03]: Rvalue and Rvalue References

### Rvalue
In C, the definition of `Rvalue` is simple: `lvalues` could stand on the left-hand side of an assignment whereas `rvalues` could not.

In C++, however, the definition is less simple. Roughly speaking, when we use an object as an `rvalue`, we use the object’s value (its contents). When we use an object as an `lvalue`, we use the object’s identity (its location in memory). To be more specific, an `lvalue` is an expression that refers to a __memory location__ and allows us to take the address of that memory location via the `&` operator. Others are `rvalues`.

#### `Lvalue` Examples.
```cpp
int i = 1;
int* ptr1 = &i;     // i is an lvalue
int& foo();
foo() = 2;
int* ptr2 = &foo(); // foo() is an lvalue
```
In the above example, suppose `foo()` is the following, then `i` would become `2` after running `foo() = 2`.
```cpp
int& foo(){
    return i;
}
```

#### `Rvalue` Examples.
```cpp
int j = 0;
int* ptr;
int foobar();
j = foobar();       // foobar() is an rvalue
j = 1;              // 1 is an rvalue
```
In the above example, suppose `foobar()` is the following, then an error will be raised after running `ptr = &foobar()`, as address-of operator `&` requires an value operand.
```cpp
int foovar(){
    return i;
}
```

---
### Rvalue References
An rvalue reference is obtained by using `&&` rather than `&`. Like any reference, an rvalue reference is just another name for an object. What is different is that an rvalue reference is a reference that must be bound to an `rvalue`. 
```cpp
int i = 2;
int &r = i;             // ok: r refers to i
int &&rr = i;           // error: cannot bind an rvalue reference to an lvalue
int &r2 = i * 2;        // error: i * 2 is an rvalue
const int &r3 = i * 2;  // ok: we can bind a reference to const to an rvalue
int &&rr2 = i * 2;      // ok: bind rr2 to the result of the multiplication
```
>__Functions that return lvalue references__, along with the __assignment__, __subscript__, __dereference__, and __prefix increment/decrement operators__, are all examples of expressions that return lvalues. We can bind an `lvalue reference` to the result of any of these expressions.

>__Functions that return a nonreference type__, along with the __arithmetic__, __relational__, __bitwise__, and __postfix increment/decrement operators__, all yield rvalues. We cannot bind an lvalue reference to these expressions, but we can bind either an `lvalue reference to const` or an `rvalue reference` to such expressions.

#### Rvalues Are Ephemeral
It should be clear that lvalues and rvalues differ from each other in an important manner: Lvalues have persistent state, whereas rvalues are either literals or temporary objects created in the course of evaluating expressions. Because rvalue references can only be bound to temporaries, we know that 

- The referred-to object is about to be destroyed
- There can be no other users of that object

These facts together mean that code that uses an `rvalue reference` is free to take over resources from the object to which the reference refers.

#### Variables Are Lvalues
It should also be noted that a variable is an lvalue; we cannot directly bind an rvalue reference to a variable even if that variable was defined as an rvalue reference type. 
```cpp
int i = 1;
int &r = i;        // ok: r refers to i
int &&rr1 = i*2;   // ok: rr refres to i*2
int &&rr2 = rr1;   // error: rr1 is an lvalue
int *ptr = &r;      
cout << *ptr;      // print out 1
ptr = &rr;
cout << *ptr;      // print out 2
```

---
### Move Operations
Rvalue reference is introduced to support `move` operations. Consider:
```cpp
template <class T> swap(T& a, T& b){
    T tmp(a);   // now we have two copies of a
    a = b;      // now we have two copies of b
    b = tmp;    // now we have two copies of tmp
}
```
But, we didn't want to have any copies of `a` or `b`, we just wanted to swap them. Let's try again:
```cpp
template <class T> swap(T& a, T& b)
{
    T tmp(std::move(a));
    a = std::move(b);   
    b = std::move(tmp);
}
```
This `move()` gives its target the value of its argument, but is not obliged to preserve the value of its source. This avoid having to copy all the elements. In other words, move is a potentially __destructive read__.

The move function really does very little work. All move does is accept either an `lvalue` or `rvalue` argument, and return it as an `rvalue` without triggering a copy construction:
```cpp
template <class T> 
typename remove_reference<T>::type&& move(T&& a){ return a; }
```
Template will be summarized in the later posts.

---
