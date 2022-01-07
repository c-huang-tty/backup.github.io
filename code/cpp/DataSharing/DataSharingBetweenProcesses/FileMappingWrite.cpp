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
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);	// open
        strcpy((char*)pBuffer, dataInit.c_str());						// write       
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);	// open
        data = timer();
        strcpy((char*)pBuffer, data.c_str());							// write
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
