#include <cassert>

// TODO: Declare Vehicle as the base class
class Vehicle {
public:
    int wheels;
};
// TODO: Derive Car from Vehicle
class Car : public Vehicle {
public:
    Car(){
        wheels = 4;
    }
};
// TODO: Derive Sedan from Car
class Sedan : public Car {
public:
    Sedan(): seats(4), trunk(true) {} 
    int seats;
    bool trunk;
};

// TODO: Update main to pass the tests
int main() {
  Sedan sedan;
  assert(sedan.trunk == true);
  assert(sedan.seats == 4);
  assert(sedan.wheels == 4);
}