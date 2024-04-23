void myFunction(int &&val) // rvalues references are lvalues
{
    std::cout << "val = " << val << std::endl;
}

int main()
{
    myFunction(42); // 1. no temporary code 2. ownership changes from caller to receiver

    // problem would not be able to do
    int i = 23;
    // myFunction(i); // rvalue reference cannot bind to lvalue
    // solution is to convert an lvalue to an rvalue (technically an xvalue)
    myFunction(std::move(i)); 
    return 0; 
}