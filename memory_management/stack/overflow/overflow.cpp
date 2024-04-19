#include <stdio.h>

// passing a pointer by value is different from passing int &stack_bottom by reference
// latter allows update on original item - equivalent ot passing a pointer and dereferencing it
void recursive(int* stack_bottom){
    int current = 0;
    printf("stack bottom: %p, current: %p \n", stack_bottom, &current);
    recursive(stack_bottom);
}

int main(){
    int stack_bottom = 0;
    recursive(&stack_bottom);
    return 0;
}
// stack bottom: 0061FF1C, current: 00424D6C
// diff 2077104 
// 2077104 / 1024 = 2028KB