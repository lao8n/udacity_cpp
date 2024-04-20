#include <iostream>
#include <stdlib.h>

class MyClass
{
    int _mymember;

public:
    MyClass()
    {
        std::cout << "Constructor is called\n";
    }

    ~MyClass()
    {
        std::cout << "Destructor is called\n";
    }

    // occurs before constructor
    void *operator new(size_t size)
    {
        std::cout << "new: Allocating " << size << " bytes of memory" << std::endl;
        void *p = malloc(size);

        return p;
    }

    void *operator new[](size_t size)
    {
        std::cout << "new: Allocating " << size << " bytes of memory" << std::endl;
        void *p = malloc(size);
        
        return p;
    }

    // occurs after destructor
    void operator delete(void *p)
    {
        std::cout << "delete: Memory is freed again " << std::endl;
        free(p);
    }

    // for security reasons will often overwrite delete with 0s to protect data etc.
    void operator delete[](void *p)
    {
        std::cout << "delete: Memory is freed again " << std::endl;
        free(p);
    }
};

int main()
{
    MyClass *p = new MyClass();
    delete p;

    // new: Allocating 20 bytes of memory
    // Constructor is called
    // Constructor is called
    // Constructor is called
    // Destructor is called
    // Destructor is called
    // Destructor is called
    // delete: Memory is freed again 
    MyClass *p = new MyClass[3]();
    delete[] p;
}