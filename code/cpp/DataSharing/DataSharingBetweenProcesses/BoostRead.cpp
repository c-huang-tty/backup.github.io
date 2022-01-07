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
