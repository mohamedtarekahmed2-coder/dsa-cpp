// ════════════════════════════════════════════════════════════════════════
// [01]  BASICS: CLASSES, POINTERS & DYNAMIC MEMORY ALLOCATION
// ════════════════════════════════════════════════════════════════════════
/*
── Classes ───────────────────────────────────────────────
Core building blocks for Object-Oriented structures containing properties and methods.

Key Notes:
    - Uses constructors (with initializer lists) for setup and destructors for cleanup.

Practical Usage / Code:
    class ClassName {
        public:
            ClassName() : memberVar(0) {}   // Initializer list constructor
            ~ClassName() {}                 // Destructor
        private:
            VariableType memberVar;
    };

── Pointers ─────────────────────────────────────────────────────────────
Variables that store the MEMORY ADDRESS of another variable.

Key Notes:
    - `&` : "Address of" operator (gets the variable's memory location).
    - `*` : Dereference operator (accesses/modifies the value at the address).
    - Always initialize pointers safely to avoid undefined behavior.

Practical Usage / Code:
    VariableType val = ;
    VariableType* ptr = &val;         // ptr holds the address of val
    *ptr = <new_value>;               // Modifies val directly through the pointer
    VariableType* safePtr = nullptr;  // Safe initialization (Modern C++)

── Pointers & Arrays ────────────────────────────────────────────────────
An array NAME is effectively a CONSTANT pointer to its first element (`arr == &arr[0]`).

Operations / Best Practices:
    - arr[i]        // Normal indexing
    - *(arr + i)    // Pointer arithmetic equivalent
    - ptr++         // OK: Pointer variables can be moved to the next address
    - arr++         // ERROR: Array names are constant pointers and cannot move

── Pointer Arithmetic Precedence ────────────────────────────────────────
The increment operator `++` has HIGHER precedence than the dereference operator `*`.

Operations:
    - *ptr++        // Get the current value, THEN advance the pointer address
    - *++ptr        // Advance the pointer address FIRST, THEN get the new value
    - (*ptr)++      // Increment the actual VALUE stored at the current address

── Pointers & Functions ────────────────────────────────────────
Passing addresses avoids copying large structures and allows direct modification.

Key Notes:
    - NEVER return a pointer to a local variable (it is destroyed after the function ends).

Practical Usage / Code:
    VariableType* getPointer(VariableType* p1, VariableType* p2) {
        if (p1 == nullptr) return p2;
        return p1;
    }

── const & Pointers ─────────────────────────────────────────────────────
Modifiers that dictate whether the pointer address or the stored value can be changed.

Operations:
    - const Type* ptr       // Pointer to CONST value (can move ptr, cannot change *ptr)
    - Type* const ptr       // CONST pointer (cannot move ptr, can change *ptr)
    - const Type* const ptr // Fully constant (cannot move ptr or change *ptr)

── References (Aliases) ─────────────────────────────────────────────────
An alternative NAME for an existing variable.

Key Notes:
    - Must match the type of the original variable.
    - Must be initialized IMMEDIATELY upon declaration.

Practical Usage / Code:
    VariableType val = ;
    VariableType& ref = val;      // ref is now an alias for val

Operations / Best Practices:
    - void fun(Type& a)           // Pass by reference (modifies original)
    - void fun(const Type& a)     // Const reference (read-only, accepts literals like `5`)
    - void fun(Type* a)           // Pass by pointer (requires passing `&val`)

── Dynamic Memory Allocation ────────────────────────────────────────────
Allocating memory on the HEAP at runtime, while the pointer remains on the STACK.

Key Notes:
    - Every `new` allocation MUST be paired with a `delete` to prevent memory leaks.

Practical Usage / Code:
    VariableType* p1 = new VariableType;            // Single element allocation
    VariableType* p2 = new VariableType(val);          // Single element initialized
    VariableType* p3 = new VariableType{val};          // Single element initialized
    delete p1;                                      // Free single element
    delete p2;
    delete p3;
    VariableType* pArr = new VariableType[<size>];  // Array allocation
    delete[] pArr;                                  // Free array memory

── Pointers to Structs or Objects ───────────────────────────────────────
Use the arrow operator `->` to access members or methods through a pointer.

Practical Usage / Code:
    ObjectName obj;
    ObjectName* ptr = &obj;
    ptr->memberVariable = val;
    ptr->methodName();

*/

#include <iostream>
using namespace std;



int main()
{   
    int** arr = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = new int[5];
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            arr[i][j] = i * j;
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }

    for (int i = 0; i <5; i++)
    {
        delete [] arr[i];
    }
    
    delete [] arr;

    
    return 0;
}