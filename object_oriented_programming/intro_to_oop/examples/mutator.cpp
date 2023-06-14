#include <string>
#include <cstring>
#include <iostream>

class Car {
    // TODO: Declare private attributes
    private:
        int horsepower;
        int weight;
        const char* brand;
        
    // TODO: Declare getter and setter for brand
    public:
        void SetHorsepower(int hp);
        void SetWeight(int w);
        void SetBrand(std::string b);
        int GetHorsepower();
        int GetWeight();
        std::string GetBrand(); 
};

// Define setters
void Car::SetHorsepower(int hp){
    horsepower = hp;
}
void Car::SetWeight(int w){
    weight = w;
}
void Car::SetBrand(std::string b){
    brand = b.c_str();
}

// Define getters
int Car::GetHorsepower(){
    return horsepower;
}
int Car::GetWeight(){
    return weight;
}
std::string Car::GetBrand(){
    std::string b = brand;
    return b;
}
// Test in main()
int main() 
{
    Car car;
    car.SetBrand("Peugeot");
    std::cout << car.GetBrand() << "\n";   
}