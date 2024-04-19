#include <iostream>
// g++ -std=c++11 example.cpp

void AddFive(int &val, bool &success)
{
    val += 3;
    success = true;
}

int main()
{
    int val = 0;
    bool success = false;
    AddFive(val, success);
    val += 2;

    std::cout << "val = " << val << ", success = " << success << std::endl;

    return 0;
}