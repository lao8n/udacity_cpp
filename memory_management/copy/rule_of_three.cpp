// Rule of Three = if a class needs to have an overload copy constructor, copy assignment operator or destructor then 
// it needs all three.
#include <stdlib.h>
#include <iostream>

class MyMovableClass
{
private:
    int _size;
    int *_data;

public:
    MyMovableClass(size_t size) // constructor
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }

    ~MyMovableClass() // 1 : destructor
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }

    MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
    {
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data; // deep copy
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }

    MyMovableClass &operator=(const MyMovableClass &source) // 3: copy assignment operator
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        if (this == &source){
            return *this; // protection against self assignment
        }
        delete[] _data;
        _data = new int[source._size];
        *_data = *source._data; // deep copy
        _size = source._size;
        return *this;
    }
};

// this is bad because 1. create memory on stack 2. copy from temporary object to target destination
// solution before c++ 11 was don't return objects by value, and after c++ 11 is to use the rule of five
MyMovableClass createObject(int size)
{
    MyMovableClass obj(size);
    return obj; // returns object by value compiler creates temporary object as rvalue
}

int main()
{
    MyMovableClass obj1(10); // regular constructor
    MyMovableClass obj2(obj1); // copy constructor
    MyMovableClass obj3(20);
    obj3 = obj1; // copy assignment operator

    MyMovableClass obj4 = createObject(30); // temporary copy does not print cout statement of copy constructor
    return 0;
}