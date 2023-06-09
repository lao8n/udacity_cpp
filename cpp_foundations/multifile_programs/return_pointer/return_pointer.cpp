#include <iostream>
using std::cout;

// be careful that do not return a pointer to a local variable
int* AddOne(int& j) 
{
    // Increment the referenced int and return the
    // address of j.
    j++;
    return &j;
}

int main() 
{
    int i = 1;
    cout << "The value of i is: " << i << "\n";
    
    // Declare a pointer and initialize to the value
    // returned by AddOne:
    int* my_pointer = AddOne(i);
    cout << "The value of i is now: " << i << "\n";
    cout << "The value of the int pointed to by my_pointer is: " << *my_pointer << "\n";
}