 For the & symbol, if it appears on the left side of an equation (e.g. when declaring a variable), it means that the variable is declared as a reference. If the & appears on the right side of an equation, or before a previously defined variable, it is used to return a memory address
 Pointer = machine address with type associated with it at compile time



References vs pointers
Both offer an alternative way to access an existing variable: pointers through the variable's address, and references through another name for that variable. 

* References must be initialized when they are declared. This means that a reference will always point to data that was intentionally assigned to it.	
* Pointers can be declared without being initialized, which is dangerous. If this happens mistakenly, the pointer could be pointing to an arbitrary address in memory, and the data associated with that address could be meaningless, leading to undefined behavior and difficult-to-resolve bugs.

* References can not be null. This means that a reference should point to meaningful data in the program.	
* Pointers can be null. In fact, if a pointer is not initialized immediately, it is often best practice to initialize to nullptr, a special type which indicates that the pointer is null.

* When used in a function for pass-by-reference, the reference can be used just as a variable of the same type would be.	
* When used in a function for pass-by-reference, a pointer must be dereferenced in order to access the underlying object.