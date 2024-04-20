#include <stdlib.h>
#include <iostream>

class MyClass
{
    private:
        int *_number;

    public:
        MyClass()
        {
            std::cout << "Allocate memory\n";
            _number = (int*)malloc(sizeof(int));
        }
        ~MyClass()
        {
            std::cout << "Delete memory\n";
            free(_number);
        }
        void setNumber(int number)
        {
            *_number = number;
            std::cout << "Number: " << *_number << "\n";
        }
};

int main()
{
    // doesn't error weirdly
    MyClass *myClass = (MyClass *)malloc(sizeof(MyClass));
    myClass->setNumber(42);
    free(myClass);

    // allocate using new
    // MyClass *myClass = new MyClass();
    // myClass->setNumber(42);
    // delete myClass;

    return 0;
}