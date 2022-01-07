## Data Sharing [C++] [04]: Between Processes

Codes in this post can be found in [DataSharingBetweenProcesses](https://github.com/c-huang-tty/c-huang-tty.github.io/tree/main/code/cpp/DataSharing/DataSharingBetweenProcesses).

Inter Process Communication (IPC) refers to a mechanism, where the operating systems allow various processes to communicate with each other. This involves synchronizing their actions and managing shared data. There are many methods to realize this, such as __Pipes__, __FIFO__, __Message Queues__, __Shared Memory__, __Semaphores__, __Signals__. In my projects, I have used __shared memory__ for sharing data between processes. We can either use __`File mapping`__ provided by Microsoft or __`boost.interprocess`__ from `boost` library.


### [File Mapping](https://docs.microsoft.com/en-us/windows/win32/memory/file-mapping)
https://docs.microsoft.com/en-us/windows/win32/memory/file-mapping

In the functions provided by Microsoft, one of the processes first creates a __`File Mapping Object`__ in the physical memory using [CreateFileMapping](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga) function. Then another process can open the file mapping using [OpenFileMappingA](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfilemappinga) function and and create a __`File View`__ in virtual memory to access the file's contents using [MapViewOfFile](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile) function. 

![text](https://docs.microsoft.com/en-us/windows/win32/memory/images/fmap.png)

The file on disk can be any file that the users want to map into memory, or it can be the system page file. Processes use __pointers__ to read from and write to the files, just as they would with dynamically allocated memory. Finally, When a process has finished with the file mapping object, it should destroy all file views in its address space by using the [UnmapViewOfFile](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile) function for each file view. Below is a sample test code. The write process write a timestamp to the file every 10 ms, and the read the timestamp and print it out. 

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

---
### [Boost Library](https://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html)

