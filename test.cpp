#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int counter = 10;  // Shared counter
mutex mtx;  // Mutex to synchronize access to 'counter'

void stopWatch(){
    for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(1s);  // Sleep for 1 second

        mtx.lock();  // Lock mutex before accessing shared variable 'counter'
        cout << "Remaining seconds: " << counter << endl;  // Print current counter
        counter--;  // Decrement counter
        mtx.unlock();  // Unlock mutex after accessing shared variable 'counter'
    }
}

void logFile(){
    while (counter > 0) {
        this_thread::sleep_for(1s);  // Sleep for 1 second

        mtx.lock();  // Lock mutex before accessing shared variable 'counter'
        if ((counter % 2 == 0)) {  // Check if the counter is even
            cout << counter << " seconds remaining" << endl;  // Print the counter value
        }
        mtx.unlock();  // Unlock mutex after accessing shared variable 'counter'
    }
}

int main() {
    thread t1(stopWatch);  // Start thread for stopwatch
    thread t2(logFile);    // Start thread for logFile

    t1.join();  // Ensure main thread waits for t1 (stopWatch) to finish
    t2.join();  // Ensure main thread waits for t2 (logFile) to finish

    return 0;  // Exit program
}

