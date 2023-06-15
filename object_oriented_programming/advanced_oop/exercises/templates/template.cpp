#include <cassert>
#include <vector>

// TODO: Declare a generic, templatized function Max()
template <typename Type> 
Type Max(Type a, Type b){ 
    if(a > b){ 
        return a; 
    } else {
        return b;
    }
}

template <typename Type>
Type Multiply(Type a, Type b){
    return a * b;
}

int main() { 
  assert(Max(10, 50) == 50);
  assert(Max(5.7, 1.436246) == 5.7);
  // need the additional bracket to help the preprocessor so it doesn't thing there are 3 arguments
  // tried to find an example where < is not defined but couldn't find one
  assert((Max(std::vector<int>{3, 4, 1}, std::vector<int>{1, 2}) == std::vector<int>{3, 4, 1}));
  // it does complain that no * operator is defined for these types so the compiler helps you a bit 
  assert((Multiply(std::vector<int>{3, 4, 1}, std::vector<int>{1, 2}) == std::vector<int>{3, 4, 1}));

}