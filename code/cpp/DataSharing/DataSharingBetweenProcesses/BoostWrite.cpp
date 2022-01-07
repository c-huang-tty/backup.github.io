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
