// g++ -std=c++11 -o minimal minimal.cpp -pthread
// does'nt work - not sure why.. thread is not a member of std
// g++ version is 6.3
#include <iostream>
#include <thread>

void helloFunction() {
    std::cout << "Hello from the thread!" << std::endl;
}

int main() {
    std::thread t(helloFunction);
    t.join();
    return 0;
}