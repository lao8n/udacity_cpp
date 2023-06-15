#include <assert.h>

// TODO: Declare a generic, templatized average function
template <typename Type>
Type average(Type a, Type b){
    return (a + b) / 2;
}
int main() { assert(average(2.0,5.0) == 3.5); }