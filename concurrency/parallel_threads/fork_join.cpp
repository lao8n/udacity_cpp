#include <iostream>
#include <thread>
#include <vector>

// threads can get preempted in the middle of execution resulting in interleaved output
// Hello from Worker thread #Hello from Worker thread #140370329347840140370337740544
// Hello from Worker thread #140370320955136
// Hello from Worker thread #140370346133248

// Hello from Main thread #140370363660096
// Hello from Worker thread #140370312562432
void printHello()
{
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
}

int main()
{
    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; ++i)
    {
        // copying thread objects causes a compile error, threads do not have a copy constructor
        /*
        std::thread t(printHello);
        threads.push_back(t); 
        */

        // moving thread objects will work
        threads.emplace_back(std::thread(printHello)); // solution is to use move semantics
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();

    return 0;
}
