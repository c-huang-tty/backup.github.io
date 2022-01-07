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
