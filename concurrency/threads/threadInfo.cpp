#include <iostream>
#include <thread>

int main()
{
    std::cout << "hello concurrent world from main! thread id = " << 
        std::this_thread::get_id() << std::endl;

    unsigned int nThreads = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nThreads << " threads" << std::endl;
    return 0;
}