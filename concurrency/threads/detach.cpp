#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work in thread\n";
}

int main()
{
    std::thread t(threadFunction);

    t.detach(); // if don't join then program will crash, detach makes it async
    // destructor of detatched thread neither blocks nor does it terminate the thread
    // be wary of using this otherwise may not call destructors properly or may still have access to data that isn't htere etc.
    // especially as cannot join a detached thread
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "Finished work in main\n";

    return 0;
}