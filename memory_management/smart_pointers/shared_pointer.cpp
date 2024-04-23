#include <iostream>
#include <memory>

// form of garbage collection similar to what happens in swift or python but it doesn't just work for memory 
// but any resource that needs to be deallocated
int main()
{
    std::shared_ptr<int> shared1(new int);
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

    {
        std::shared_ptr<int> shared2 = shared1;
        std::cout << "shared pointer count = " << shared1.use_count() << std::endl;
    }
    
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

    // also shared1.reset(new int) // deletes the old pointer and assigns a new one
    // be careful of circular references - solution is weak pointers
    return 0;
}