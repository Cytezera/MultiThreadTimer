#include <mutex>
#include <iostream>
#include <thread>
#include <fstream>
#include <chrono> 

using namespace std; 

int counter = 10; 
mutex mtx; 

void stopWatch(){
	for (int i = 0; i < 10 ; i ++ ) {
		this_thread::sleep_for(1s);
		mtx.lock();
		cout << "Remaining seconds: " << counter << endl; 
		counter --; 
		mtx.unlock();
	}	
}

void logFile(){
	while (counter > 0) {
		this_thread::sleep_for(1s); 
		mtx.lock();
		if ((counter % 2  == 0 )) {
			
			cout << counter <<" seconds remaining" << endl;
		}
		
		mtx.unlock();
	}
}	

int main() {
	thread t1(stopWatch); 	
	thread t2(logFile); 
	t2.join();
	t1.join(); 
	return 0 ; 
}
