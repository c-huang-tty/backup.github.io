## Data Sharing [C++] [03]: Between Threads


#### Reference Parameters Tips
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
The result is `error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’`. As `3` and `4` are `rvalues`, we cannoy assign it to `lvalues` like `a` and `b`. We should call the function like below, which will print the same results.
```cpp
int a = 3, b = 4, sum, diff;
SumDiff(a,b,sum,diff);
cout << "sum is: " << sum << " " << "diff is: " << diff << endl;
```
The same issue is with the second example.
