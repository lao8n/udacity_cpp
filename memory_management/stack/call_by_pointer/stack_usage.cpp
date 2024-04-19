#include <stdio.h>
    
void CallByValue(int i)
{
    int j = 1; 
    printf ("call-by-value: %p\n",&j);
}

void CallByPointer(int *i)
{
    int j = 1; 
    printf ("call-by-pointer: %p\n",&j);
}

void CallByReference(int &i)
{
    int j = 1; 
    printf ("call-by-reference: %p\n",&j);
}

// stack bottom: 0061FF1C
// call-by-value: 0061FEEC - why is this the same? because size of pointer == size of int
// call-by-pointer: 0061FEEC
// call-by-reference: 0061FEEC
// not copying is only worth it if larger than pointer
int main()
{
    int i = 0;
    printf ("stack bottom: %p\n",&i);
    
    CallByValue(i);

    CallByPointer(&i);

    CallByReference(i);

    return 0;
}