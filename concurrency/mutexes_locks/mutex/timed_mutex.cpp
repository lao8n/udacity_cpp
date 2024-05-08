#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include<algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int iD(){
        return _id;
    }
private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() {}

    // getters / setters
    void printSize()
    {
        _mutex.lock();
        std::cout << "#vehicles = " << _vehicles.size() << std::endl;
        _mutex.unlock();
    }
    
    // typical behaviour methods
    void pushBack(Vehicle &&v)
    {
        int attempts = 0;
        while(attempts < 3){
            if(_mutex.try_lock_for(std::chrono::milliseconds(10))){
                _vehicles.emplace_back(std::move(v)); // data race would cause exception
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                _mutex.unlock();
                return;
            } 
            attempts++;
            std::cout << "Attempt to lock for vehicle id " << v.iD() << " failed " << attempts << " times " << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        // give up
    }

private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::timed_mutex _mutex;
};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles); 
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 1000; ++i)
    {
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    queue->printSize();

    return 0;
}
