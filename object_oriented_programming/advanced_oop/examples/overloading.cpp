#include <iostream>

// TODO: Write hello() function
void hello(){ std::cout << "Hello, World!" << "\n"; };
// TODO: Overload hello() three times
class Human{};
void hello(Human human){ std::cout << "Hello, Human!" << "\n"; };
class Alien{};
void hello(Alien alien){ std::cout << "Hello, Alien!" << "\n"; };

// TODO: Call hello() from main()
int main(){
    hello();
    hello(Human());
    hello(Alien());
}