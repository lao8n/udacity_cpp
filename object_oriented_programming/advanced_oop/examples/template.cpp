#include<cassert>
#include<iostream>

// C++ 20 allows for concepts the use of the keyword 'requires' to constrain template parameters
// this precisely defines the requirements for the template parameters
template <typename Type> Type Product(Type a, Type b) { return a * b; }

int main(){
    assert(Product<int>(3, 4) == 12);
}