## Data Sharing [C++] [04]: Between Processes

Codes in this post can be found in [DataSharingBetweenProcesses](https://github.com/c-huang-tty/c-huang-tty.github.io/tree/main/code/cpp/DataSharing/DataSharingBetweenProcesses).

Inter Process Communication (IPC) refers to a mechanism, where the operating systems allow various processes to communicate with each other. This involves synchronizing their actions and managing shared data. There are many methods to realize this, such as __Pipes__, __FIFO__, __Message Queues__, __Shared Memory__, __Semaphores__, __Signals__. In my projects, I have used __shared memory__ for sharing data between processes. We can either use __`File mapping`__ provided by Microsoft or __`boost.interprocess`__ from `boost` library.


### [File Mapping](https://docs.microsoft.com/en-us/windows/win32/memory/file-mapping)
https://docs.microsoft.com/en-us/windows/win32/memory/file-mapping

In the functions provided by Microsoft, process 1 first creates a __`File Mapping Object`__ in the physical memory using [CreateFileMapping](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga) function. Then process 2 can open the file mapping using [OpenFileMapping](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfilemappinga) function and and create a __`File View`__ in virtual memory to access the file's contents using [MapViewOfFile](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile) function. 

![text](https://docs.microsoft.com/en-us/windows/win32/memory/images/fmap.png)

The file on disk can be any file that the users want to map into memory, or it can be the system page file. Processes use __pointers__ to read from and write to the files, just as they would with dynamically allocated memory. Finally, When a process has finished with the file mapping object, it should destroy all file views in its address space by using the [UnmapViewOfFile](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile) function for each file view. Below is a sample test code. The write process writes a timestamp to the file every 10 ms, and the read process reads the timestamp and print it out. 

```cpp
// Write Process

#include <Windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;
#pragma warning(disable:4996)
string timer();

int main(){
    string strMapName("ShareMemory");                
    string strComData("This is common data!");        
    LPVOID pBuffer;                                   
    LPVOID pBufferOld;                                   

    HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, (LPCWSTR)strMapName.c_str());
    if (NULL == hMap){    
        // Fail, create a file mapping
        hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,
                                   NULL,
                                   PAGE_READWRITE,
                                   0,
                                   strComData.length() + 1,
                                   (LPCWSTR)strMapName.c_str());

        // Create a file view and write data to the shared ameamory
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        strcpy((char*)pBuffer, strComData.c_str());
        cout << "Write data to shared memory: " << (char*)pBuffer << endl;
    }
    else{    
        // Succeed, create a file view and read data from the shared memory
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        cout << "Read data from shared memory: " << (char*)pBuffer << endl;
	}
    
    while (1) {
        // Initialize the file with "0"
        string dataInit = "0";
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);  // open
        strcpy((char*)pBuffer, dataInit.c_str());                       // write       
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);  // open
        data = timer();
        strcpy((char*)pBuffer, data.c_str());                           // write
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}         

    // Release
    ::UnmapViewOfFile(pBuffer);
    ::CloseHandle(hMap);

    return 0;
}

string timer() {
    // current date/time based on current system
    static stringstream timeS;
    static time_t now;
    static tm* ltm;

    now = time(0);
    ltm = localtime(&now);
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    timeS.str("");
    timeS << 1900 + ltm->tm_year << "." << 1 + ltm->tm_mon << "." << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "." << millisec_since_epoch % 1000;

    return timeS.str();
}
```

```cpp
// Read Process

#include <Windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;

#pragma warning(disable:4996)

int main(){
    string strMapName("ShareMemory");                
    string strComData("This is common data!");        
    LPVOID pBuffer;                                   
    LPVOID pBufferOld;                                   

    HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, (LPCWSTR)strMapName.c_str());
    if (NULL == hMap){    
        // Fail, create a file mapping
        hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,
                                   NULL,
                                   PAGE_READWRITE,
                                   0,
                                   strComData.length() + 1,
                                   (LPCWSTR)strMapName.c_str());

        // Create a file view and write data to the shared ameamory
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        strcpy((char*)pBuffer, strComData.c_str());
        cout << "Write data to shared memory: " << (char*)pBuffer << endl;
    }
    else{    
        // Succeed, create a file view and read data from the shared memory
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        cout << "Read data from shared memory: " << (char*)pBuffer << endl;
	}
    
    while (1) {
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0); 
        string dataS((char*)pBuffer);
        if (dataS[0] == '2') {
            cout << "Timestamp: " << dataS << endl;
        }
    }         

    // Release
    ::UnmapViewOfFile(pBuffer);
    ::CloseHandle(hMap);

    return 0;
}
```

#### Fallible Points


---
### [Boost Library](https://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html)
https://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html

Realizing shared memory using boost library is also very simple. 

Fisrt, process 1 requests to the operating system a memory segment that can be shared between processes using the [shared_memory_object](https://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html#interprocess.sharedmemorybetweenprocesses.sharedmemory.shared_memory_creating_shared_memory_segments) `class`. After setting the size of the memory using `shared_memory_object.truncate(SIZE_OF_MEMORY)`. The process can map the whole shared memory or just part of it. The mapping process is done using the [mapped_region](https://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html#interprocess.sharedmemorybetweenprocesses.sharedmemory.shared_memory_creating_shared_memory_segments) `class`. 

Then process 2 can access the shared memory according to the name of the memory, just like that with the __File Mapping__. 

Finally, the memory should be removed using method `shared_memory_object::remove("NAME")`.

Below is a sample test code. The write process writes ‘1’s to the shared memory, and the read process prints it out. 

```cpp
// Write Process

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

using namespace boost::interprocess;
using namespace std;

int main(){
    cout << "P1 started" << endl;
	
    this_thread::sleep_for(chrono::milliseconds(10u));
	
    // Create a shared memory object
    shared_memory_object shm(create_only, "MySharedMemory", read_write);
	
    // Set size
    shm.truncate(100);
	
    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);
	
    // Write all the memory to 1
    std::memset(region.get_address(), 1, region.get_size());
	
    cout << "P1 ended" << endl;
	
    return 0;
}
```

```cpp
// Read Process

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

using namespace boost::interprocess;
using namespace std;

int main(){
    cout << "P2 started" << endl;
	
    // Create a shared memory object
    shared_memory_object shm(open_only, "MySharedMemory", read_only);
	
    //Map the whole shared memory in this process
    mapped_region region(shm, read_only);
	
    const char* mem = static_cast<char*>(region.get_address());

    // check the memory
    bool isError = false;
    for(auto i = 0u; i < region.get_size(); ++i){
        const int data = *(mem + i);
        printf("data %i is %d\n", i, data);
        if (data != 1) {
            isError = true;
            break;
        }
    }
    // Realease
    shared_memory_object::remove("MySharedMemory");
	
    cout << "P2 ended" << endl;
	
    return 0;
}
```
