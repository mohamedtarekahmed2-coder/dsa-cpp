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

// ════════════════════════════════════════════════════════════════════════
// [02]  Big O Notation
// ════════════════════════════════════════════════════════════════════════
/*
Measures how the number of operations GROWS with input size N.
Rule of Thumb:  1 Second ≈ 10^8 ~ 10^9 operations (practically use 10^8).

COMPLEXITY RANKINGS (Best → Worst):
┌─────────────────┬───────────────┬──────────────────────────────────────┐
│  Big O          │  Name         │  Example                             │
├─────────────────┼───────────────┼──────────────────────────────────────┤
│  O(1)           │  Constant     │  arr[5], min(a,b), swap(a,b)         │
│  O(log N)       │  Logarithmic  │  binary_search, lower_bound          │
│  O(N)           │  Linear       │  Single loop over N elements         │
│  O(N log N)     │  Linearithmic │  sort(arr, arr + n)                  │
│  O(N^2)         │  Quadratic    │  Two nested loops                    │
│  O(c^N)         │  Exponential  │  Recursive subsets                   │
│  O(N!)          │  Factorial    │  next_permutation (all permutations) │
└─────────────────┴───────────────┴──────────────────────────────────────┘

Speed ranking (Fastest -> Slowest):
    O(1) < O(log N) < O(N) < O(N log N) < O(N^2) < O(c^N) < O(N!)

HOW TO CALCULATE BIG O:
    Step 1: Count the expected number of instructions based on input size.
    Step 2: Drop all constants.       e.g., n^2/2 + 30n  →  n^2 + n
    Step 3: Keep the dominant term.   e.g., n^2 + n       →  O(n^2)
    Note:   O(n), O(2n), O(3n) are all treated as O(n).

SPACE COMPLEXITY:
    Same concept as Time Complexity but measures MEMORY used instead.
    Also expressed using Big O notation.

TLE / MLE VERDICTS:
    - TLE (Time Limit Exceeded):   solution exceeds allowed run time.
    - MLE (Memory Limit Exceeded): solution exceeds allowed memory.
    - Both mean your logic may be correct but your complexity is too high.
    - Example: N <= 100,000
        O(N log N) ≈ 10^6  → OK
        O(N^2)     ≈ 10^10 → TLE

BUILT-IN FUNCTIONS COMPLEXITY:
    O(1):       min(a,b), max(a,b), swap(a,b)
    O(log N):   binary_search, lower_bound, upper_bound
    O(N):       pow(a,n), reverse, min_element, max_element, fill, count, find
    O(N log N): sort(arr, arr + n)
    O(N!):      next_permutation(arr, arr + n)

*/

// ════════════════════════════════════════════════════════════════════════
// [03]  VECTOR (DYNAMIC ARRAY)
// ════════════════════════════════════════════════════════════════════════
/*
── Core Structure & Memory Management ───────────────────────────────────────────────
A vector is a dynamic, flexible array that manages its own heap-allocated memory. It abstracts away raw pointer manipulation while allowing dynamic resizing.

Key Notes:
    - Requires tracking an internal pointer (`arr`), current active elements (`size`), 
        and total allocated space (`capacity`).
    - Constructor must safely allocate memory using `new[]`.
    - Destructor MUST deallocate memory using `delete[]` to prevent memory leaks.
    - Bounds checking should always be enforced on element access operations.

Practical Usage / Commands / Code:
    class Vector {
    private:
        int* arr = nullptr;
        int size = 0;
        int capacity = 0;

    public:
        // Initialization
        Vector(int initial_size) {
            if(initial_size < 0) initial_size = 1;
            this->size = initial_size;
            this->capacity = initial_size;
            arr = new int[capacity]{}; 
        }
        
        // Cleanup
        ~Vector() {
            delete[] arr; 
            arr = nullptr;
        }
    };

Operations / Best Practices:
    - get(index)            // O(1) Accesses element at index if bounds (0 <= index < size) are valid.
    - set(index, val)       // O(1) Mutates element at index if bounds are valid.
    - find(val)             // O(N) Linear search; iterates through array to find value.
    - get_front()           // O(1) Returns arr[0].
    - get_back()            // O(1) Returns arr[size - 1].

── Appending & Capacity Trick ───────────────────────────────────────────────
Growing an array sequentially by 1 element is highly inefficient. 
The "Capacity Trick" solves this by pre-allocating extra space (usually doubling it) to reduce reallocation frequency.

Key Notes:
    - Bad approach: Reallocating an array of `size + 1` for every insertion yields O(N) time complexity per push.
    - Good approach: Doubling `capacity` when full reduces the frequency of copying, achieving O(1) Amortized time complexity.
    - Expansion steps: Allocate larger array -> Copy old elements -> Swap pointers -> Delete old array memory.

Practical Usage / Commands / Code:
    // Internal Expansion Logic
    void expand_capacity() {
        capacity *= 2;
        int* new_arr = new int[capacity]{};
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];
        swap(new_arr, arr); 
        delete[] new_arr; 
    }

    // Optimized Insertion
    void push_back(int val) {
        if(size == capacity)
            expand_capacity();
        arr[size++] = val;
    }

Operations / Best Practices:
    - push_back_bad(val)    // O(N) Time: Avoid resizing by exactly +1 every insertion.
    - push_back(val)        // O(1) Amortized Time: Use the capacity trick for efficient appends.

*/



#include <iostream>
using namespace std;

int main()
{
    return 0;
}