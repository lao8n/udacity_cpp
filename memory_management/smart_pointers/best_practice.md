R. 10: Avoid malloc and free While the calls (MyClass*)malloc( sizeof(MyClass) ) and new MyClass both allocate a block of memory on the heap in a perfectly valid manner, only new will also call the constructor of the class and free the destructor. To reduce the risk of undefined behavior, malloc and free should thus be avoided.

R. 11: Avoid calling new and delete explicitly Programmers have to make sure that every call of new is paired with the appropriate delete at the correct position so that no memory leak or invalid memory access occur. The emphasis here lies in the word "explicitly" as opposed to implicitly, such as with smart pointers or containers in the standard template library.

R. 12: Immediately give the result of an explicit resource allocation to a manager object It is recommended to make use of manager objects for controlling resources such as files, memory or network connections to mitigate the risk of memory leaks. This is the core idea of smart pointers as discussed at length in this section

R. 20 : Use unique_ptr or shared_ptr to represent ownership

R. 21 : Prefer unique_ptr over std::shared_ptr unless you need to share ownership

R. 22 : Use make_shared() to make shared_ptr

R. 23 : Use make_unique() to make std::unique_ptr

R. 24 : Use weak_ptr to break cycles of shared_ptr

R. 30 : Take smart pointers as parameters only to explicitly express lifetime semantics

R. 33: Take a unique_ptr& parameter to express that a function reseats the widget

R. 34: Take a shared_ptr parameter to express that a function is part owner

R. 35: Take a shared_ptr& parameter to express that a function might reseat the shared pointer

```
// pass pointer or reference if only meant to read (careful with raw pointers - assume that sending code owns)
// use smart pointers only if meant to update ownership/do something with it
void f( object* );  // (a) - advantage is can be null whereas reference cannot be
void f( object& ); // (b) - default
void f( unique_ptr<object> ); // (c) best for consuming pointer - don't use const
void f( unique_ptr<object>& ); // (d) if want to modify ptr but not take ownership don't use const
void f( shared_ptr<object> ); // (e) make a copy so reference counter increments
void f( shared_ptr<object>& ); // (f) if want to modify and re-use in caller
```
a & b are preferred