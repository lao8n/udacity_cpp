#include <iostream>
#include <thread>

// -pthread is needed to comiple code with g++ as it adds support for multithreading with the pthreads library
// g++ -std=c++14 -o threadFunction threadFunction.cpp -pthread
void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread\n";
}

int main()
{
    std::thread t(threadFunction);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "Finished work in main\n";

    t.join();

    return 0;
}