#include <iostream>
#include <string>

// Define base class Animal
class Animal{
    public:
        Animal(std::string color, std::string name, int age): color_(color), name_(name), age_(age){}
        std::string color_;
        std::string name_;
        int age_;
};
// Declare derived class Snake
class Snake : public Animal {
    public:
        Snake(std::string color, std::string name, int age, int length): Animal(color, name, age), length_(length){}
        int length_;
        void MakeSound(){
            std::cout << "Hsss" << "\n";
        }
};

// Declare derived class Cat
class Cat : public Animal {
    public: 
        Cat(std::string color, std::string name, int age, int height): Animal(color, name, age), height_(height){}
        int height_;
        void MakeSound(){
            std::cout << "Miao" << "\n";
        }
};

// Test in main()
int main(){
        Snake snake("green", "arbok", 2, 1);
        snake.MakeSound();
        Cat cat("black", "miao", 3, 1);
        cat.MakeSound();
}