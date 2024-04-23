// a wrapper around pointers using RAII (resource acquisition is initialization) to manage memory
// overload * and -> operators to access the underlying pointer, and guarantee data is properly deallocated
// raii is a form of garbage collection

// c++ 11 introduced 3 types of pointers
// 1. unique_ptr - exclusive ownership, cannot be copied, can be moved
// 2. shared_ptr - shared ownership, can be copied, can be moved
// 3. weak_ptr - weak ownership, can be copied, can be moved

#include <memory>

void RawPointer()
{
    int *raw = new int; // create a raw pointer on the heap
    *raw = 1;
    delete raw; // delete the resource once finished
}

void UniquePointer()
{
    std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
    *unique = 2; // can transfer with auto destPtr = std::move(unique);
    // delete is not necessary, will be automatically deleted when out of scope
}