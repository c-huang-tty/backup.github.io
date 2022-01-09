## Data Sharing [C++] [03]: Between Threads


#### Typical Usages of Reference Parameters
__Use reference to avoid copies__

1. When it's insufficient to copy objects that are large 
2. When objects have a type that cannot be copied

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

void SumDiff(const int a, const int b, int& sum, int& diff){
    sum = a + b;
    diff = abs(a - b);
}
int main(){
    int sum, diff;
    SumDiff(3,4,sum,diff);
    cout << "sum is: " << sum << " " << "diff is: " << diff << endl;
}
```
