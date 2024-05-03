#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
};


int main()
{
    // create thread 
    // std::thread t(Vehicle()); // C++'s most vexing parse
    // two possible interpretations
    // 1. t init with anonymous instance of vehicle
    // 2. a function declaration for a function t which returns a thread and has a single unnamed parameter that is a pointer to a function returning a vehicle object
    // c++ compiler assumes it is the second, although most programmers would assume it is the first
    // ways to make it the first include
    std::thread t1( (Vehicle()) ); // extra parentheses
    std::thread t2 = std::thread( Vehicle() ); // using copy initialization
    std::thread t3{ Vehicle() }; // using uniform initialization with braces

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}