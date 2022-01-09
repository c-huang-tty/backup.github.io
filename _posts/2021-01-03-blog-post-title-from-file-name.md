## Data Sharing [C++] [03]: Between Threads


#### Typical Usages of Reference Parameters
1. Use reference to avoid copies
    - When it's insufficient to copy objects that are large 
    - When objects have a type that cannot be copied
    
    Below is an exanple comparing the length of two strings, as the string maybe long, it's betwwer to avoid copying them.
    ```cpp
    // compare the length of two strings
    bool isShorter(const string &s1, const string &s2){
        return s1.size() < s2.size();
    }
    ```
2. Use reference to return multiple variables 
