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
A vector is a dynamic, flexible array that manages its own heap-allocated memory.
It abstracts away raw pointer manipulation while allowing dynamic resizing.

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

// ════════════════════════════════════════════════════════════════════════
// [04]  HASHING (UNORDERED MAP & SET)
// ════════════════════════════════════════════════════════════════════════
/*
── What is a Hash Table ───────────────────────────────────────────────
A data structure storing key-value pairs that uses a hash function to compute an index for extremely fast data retrieval.

Key Notes:
    - Average Time Complexity: O(1) for Insert, Delete, and Search.
    - Worst Time Complexity: O(N) (Occurs when many keys hash to the same index/bucket).
    - Space Complexity: O(N).

Practical Usage / Commands / Code:
    // Conceptual Structure:
    int index = HashFunction(key) % ArraySize;
    TableArray[index] = value;

Operations / Best Practices:
    - Determinism      // The same key must ALWAYS compute the same hash code.
    - Uniformity       // A good hash function distributes keys evenly to minimize collisions.

── Collision Resolution ───────────────────────────────────────────────
Techniques used when two distinct keys yield the same hash index.

Key Notes:
    - Chaining (Open Hashing): The default in C++ STL. Each array bucket holds a linked list of colliding elements.
    - Open Addressing: Elements are stored directly in the array. Probes for next empty slot if full.
    * Linear Probing: Checks index + 1, + 2, + 3...
    * Quadratic Probing: Checks index + 1², + 2², + 3²...

Practical Usage / Commands / Code:
    // Chaining Concept:
    TableArray[index] --> Node(Key1) --> Node(Key2) --> nullptr

── Hash Implementation Logic (Chaining) ───────────────────────────────────────────────
Under the hood, it combines an array with pointers to linked lists. Tracks "Load Factor" to maintain O(1) speed.

Key Notes:
    - Load Factor = (Total Elements) / (Total Buckets).

Practical Usage / Commands / Code:
    // Generic Node Structure
    struct HashNode {
        KeyType key;
        ValueType val;
        HashNode* next;
    };

    // Generic Hash Table Outline
    class HashTable {
    private:
        HashNode** tableArray;
        int arraySize;
        int totalElements;

        int hashFunction(KeyType key) { return key % arraySize; }
        void rehash(int newSize);

    public:
        void insert(KeyType key, ValueType val); // O(1) inserts at head of chain, checks load factor
        ValueType get(KeyType key);              // O(1) finds index, traverses chain if needed
        void remove(KeyType key);                // O(1) removes node from chain, checks load factor
    };

── Rehashing ───────────────────────────────────────────────
Dynamically resizing the internal array when the Load Factor crosses specific thresholds to prevent O(N) degradation.

Key Notes:
    - Upsizing: Usually triggers when Load Factor >= 0.75 (Table size is doubled).
    - Downsizing: Usually triggers when Load Factor <= 0.25 (Table size is halved).

Practical Usage / Commands / Code:
    // Generic Rehash Structure:
    void rehash(int newSize) {
        HashNode oldTable = tableArray;

        tableArray = new HashNode*[newSize];
        // 1. Initialize all newTable buckets to nullptr
        // 2. Traverse oldTable nodes, recompute hash with newSize, link to newTable
        // 3. delete[] oldTable (only the array, do not delete the nodes themselves)
    }

── Hash Containers ───────────────────────────────────────────────
Natively implemented unordered containers that prioritize 
O(1) average lookup speed over maintaining sorted element order.

Key Notes:
    - std::unordered_map: Stores unique key-value pairs.
    - std::unordered_set: Stores unique keys only.
    - Custom key types require an overloaded operator== and a custom hash functor.
    - Worst-case O(N) time complexity occurs due to severe hash collisions or frequent rehashing.

Time Complexity:
    - Search / Lookup: O(1) average, O(N) worst-case.
    - Insertion:       O(1) average, O(N) worst-case.
    - Deletion:        O(1) average, O(N) worst-case.

Practical Usage / Commands / Code:
    #include <unordered_map>
    #include <unordered_set>

    // Standard declaration
    std::unordered_map<KeyType, ValueType> mapName;
    std::unordered_set<KeyType> setName;

    // Custom Key Support Structure
    struct KeyType {
        MemberType member;
        bool operator==(const KeyType& other) const {
            return member == other.member;
        }
    };
    struct KeyHash {
        std::size_t operator()(const KeyType& k) const {
            return std::hash<MemberType>{}(k.member);
        }
    };
    std::unordered_map<KeyType, KeyHash ValueType,> customMap;

    // Efficient existence check (C++20)
    if (setName.contains(keyVal)) { 
        // Element found in O(1) average time
    }

Operations / Best Practices:
    - mapName[key] = val;       // Inserts val if key is missing; updates val if key exists.
    - mapName.at(key);          // Returns value; throws std::out_of_range exception if key is missing.
    - setName.contains(key);    // Returns true if key exists, false if not (C++20, O(1) avg time).
    - mapName.count(key);       // Returns 1 if key exists, 0 if not (pre-C++20 existence check).
    - mapName.erase(key);       // Removes key-value pair/element in O(1) average time.
*/


#include <iostream>
using namespace std;

int main()
{
    return 0;
}