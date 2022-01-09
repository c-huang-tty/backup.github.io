## Data Sharing [C++] [03]: Between Threads


#### Typical Usages of Reference Parameters
##### Use reference to avoid copies
1. When it's insufficient to copy objects that are large 
2. When objects have a type that cannot be copied

Below is an exanple comparing the length of two strings, as the string maybe long, it's better to avoid copying them.
```cpp
// compare the length of two strings
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}
```    
    
##### Use reference to return multiple variables 
