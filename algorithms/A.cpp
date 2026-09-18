// ════════════════════════════════════════════════════════════════════════
// [01] STATIC RANGE QUERIES (PREFIX & SUFFIX)
// ════════════════════════════════════════════════════════════════════════
/*
── The Core Prefix & Suffix Concept ────────────────────────────
The core concept relies on precomputing cumulative data from array boundaries to optimize queries.
- Prefix: 
    Accumulates data from the front (left-to-right, index 1 to X) to answer queries relative to the start.
- Suffix: 
    Accumulates data from the back (right-to-left, index arraySize down to X) to answer queries relative to the end.
- Operational Rule: 
    Arbitrary mid-range [L, R] queries can only be answered in O(1) if the operation is completely invertible (e.g., +, ^).
    Non-invertible operations (e.g., min, max) can only query from boundaries to X in O(1).

── Range Queries (Prefix Sum & XOR) ───────────────────────────────
Precomputes cumulative array states to answer arbitrary range queries over a static container in constant time.

Key Notes:
    - Range Sum [L, R]: prefixSum[R] - prefixSum[L - 1]
    - Range XOR [L, R]: prefixXor[R] ^ prefixXor[L - 1]
    - Crucial Property: Valid because variableName ^ variableName = 0 (self-inverse cancels out elements outside [L, R]).
    - Time Complexity: O(N) precomputation, O(1) per range query.
    - Space Complexity: O(N) auxiliary storage array.
    - Edge Case: Must use 1-based indexing to prevent out-of-bounds errors when calculating (L - 1).

Practical Usage & Code:
    // Building prefix arrays (1-based indexing)
    for (size_t indexName = 1; indexName <= arraySize; ++indexName) {
        prefixSum[indexName] = prefixSum[indexName - 1] + containerName[indexName];
        prefixXor[indexName] = prefixXor[indexName - 1] ^ containerName[indexName];
    }

Operations:
    querySum = prefixSum[R] - prefixSum[L - 1]       // Compute range sum: O(1)
    queryXor = prefixXor[R] ^ prefixXor[L - 1]       // Compute range XOR: O(1)

── Prefix & Suffix (Max / Min) ───────────────────────
Accumulates running maximums or minimums from array boundaries up to a target index.

Key Notes:
    - Cannot answer arbitrary [L, R] range queries because max/min are non-invertible operations.
    - Prefix Max: Tracks the highest value found from the front (index 1 up to X).
    - Suffix Max: Tracks the highest value found from the back (index arraySize down to X).
    - Time Complexity: O(N) precomputation, O(1) boundary-to-X lookup.
    - Edge Case: Use arraySize + 2 for the suffix storage array to handle boundary + 1 out-of-bounds safely.

Practical Usage & Code:
    vector<dataType> prefixMax(arraySize + 1, 0);
    vector<dataType> suffixMax(arraySize + 2, 0);

    // Precomputing running maximum from front (Prefix)
    prefixMax[1] = containerName[1];
    for (size_t indexName = 2; indexName <= arraySize; ++indexName) {
        prefixMax[indexName] = max(prefixMax[indexName - 1], containerName[indexName]);
    }

    // Precomputing running maximum from back (Suffix)
    suffixMax[arraySize] = containerName[arraySize];
    for (size_t indexName = arraySize - 1; indexName >= 1; --indexName) {
        suffixMax[indexName] = max(suffixMax[indexName + 1], containerName[indexName]);
    }

Operations:
    prefixMax[variableX]    // Get max from start to index X: O(1)
    suffixMax[variableX]    // Get max from index X to end: O(1)

── Difference Array (Deferred Range Updates) ─────────────────────
Modifies elements across an entire range [L, R] simultaneously by deferring calculations.
You can create this array and then iterate over it again using Prefix.

Key Notes:
    - Strict Edge Case: Only useful if all update queries occur completely before reading the final array values (static updates).
    - Rule: To add valueName to range [L, R], increment position L and decrement position R + 1.
    - Final Pass: Uses the Prefix Sum concept to pass over the updates and reconstruct final array values.
    - Time Complexity: O(1) per range update, O(N) for final reconstruction pass.

Practical Usage & Code:
    vector<dataType> differenceArray(arraySize + 2, 0);

    // Deferring execution for range [L, R] with valueName
    differenceArray[L] += valueName;
    differenceArray[R + 1] -= valueName;

    // Executing prefix sum pass to reconstruct and apply modifications
    for (size_t indexName = 1; indexName <= arraySize; ++indexName) {
        differenceArray[indexName] += differenceArray[indexName - 1];
        containerName[indexName] += differenceArray[indexName];
    }

Operations:
    differenceArray[L] += valueName;       // Start range marker: O(1)
    differenceArray[R + 1] -= valueName;   // End range marker: O(1)

── Single-Array Prefix-Suffix Optimization ───────────────────────────
An optimization technique to compute prefix and suffix operations
(like sum, product, or min/max) using only a single array instead of
allocating two separate arrays, reducing auxiliary space complexity from O(N) to O(1).

Key Notes (Keep it brief):
    - Time Complexity: O(N) to compute both passes.
    - Space Complexity: O(1) auxiliary space (excluding the output array).
    - Core Concept: Perform a forward pass to store the prefix, then a backward
    pass to apply the suffix dynamically using a single accumulator variable.

Practical Usage & Code:
    void computePrefixSuffix(vector& arrayName) {
        size_t sizeValue = arrayName.size();
        vector resultArray(sizeValue, initialValue);

        // Step 1: Forward pass (Prefix accumulation)
            resultArray[0] = identityValue;
            for (size_t i = 1; i < sizeValue; ++i) {
                resultArray[i] = resultArray[i - 1] * arrayName[i - 1];
            }

        // Step 2: Backward pass (Suffix accumulation on the fly)
            dataType suffixAccumulator = identityValue;
            for (int i = static_cast<int>(sizeValue) - 1; i >= 0; --i) {
                resultArray[i] *= suffixAccumulator;
                suffixAccumulator *= arrayName[i];
            }
    }

Operations:
    arrayName[i] += arrayName[i - 1]     // In-place Prefix Sum: O(N) time, O(1) space
    suffixAccumulator *= arrayName[i]    // Dynamic Suffix update: O(1) per step

── 2D Prefix Sum (Submatrix Queries) ───────────────────────────────────────────────
Precomputes cumulative sums of a 2D grid to enable instantaneous submatrix sum queries.
Each cell (i, j) in the prefix matrix stores the total sum from the top-left origin up to (i, j).

Key Notes (Keep it brief):
    - Construction Time: O(rows * cols)
    - Space Complexity: O(rows * cols)
    - Query Time: O(1) per query
    - Edge Case mitigation: Use a 1-based index (pad top and left with zeros)
        for the prefix matrix to prevent out-of-bounds (index -1) access on boundaries.

Practical Usage & Code:
    // 1-based indexing prefix matrix initialized to 0
    vector<vector<dataType>> prefixName(rows + 1, vector(cols + 1, 0));

    // Construction (assuming matrixName is 0-indexed)
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            prefixName[i][j] = matrixName[i-1][j-1] + prefixName[i-1][j] + prefixName[i][j-1] - prefixName[i-1][j-1];
        }
    }
Operations:
    // Query submatrix sum from top-left (r1, c1) to bottom-right (r2, c2)
    // NOTE: r1, c1, r2, c2 must be converted to 1-based indices before querying
    dataType resultName = prefixName[r2][c2] - prefixName[r1-1][c2] - prefixName[r2][c1-1] + prefixName[r1-1][c1-1];  // Get area sum: O(1)

*/

// ════════════════════════════════════════════════════════════════════════
// [02] TWO POINTERS & SLIDING WINDOW
// ════════════════════════════════════════════════════════════════════════
/*
── Two Pointers ────────────────────────────────────────────────────────
Efficient technique to find two elements in a collection that satisfy a
specific target condition by moving boundaries inward.

Key Notes:
    - The array MUST be sorted before using this approach.
    - Time Complexity: O(N) assuming the collection is already sorted.
    - Space Complexity: O(1) as it only uses index variables.

Practical Usage / Commands / Code:
    int <left_ptr> = 0;
    int <right_ptr> = .size() - 1;

    while (<left_ptr> < <right_ptr>) {
        int <current_sum> = <array>[<left_ptr>] + <array>[<right_ptr>];

        if (<current_sum> == <target>) return true;
        else if (<current_sum> < <target>) <left_ptr>++;
        else <right_ptr>--;
    }

Operations / Best Practices:
    - Sort First            // Use sort(.begin(), .end()) before setting pointers.
    - Prevent Overflow      // Use long long for <current_sum> if array elements are large.

── Sliding Window ──────────────────────────────────────────────────────
A dynamic two-pointer method used to efficiently evaluate contiguous
subarrays or substrings that meet a specific condition (e.g., target sum).

Key Notes:
    - Expand the "window" by moving the right pointer to include elements.
    - Shrink the "window" by moving the left pointer to find optimal sizes or restore validity.
    - Time Complexity: O(N), highly efficient as each element is visited at most twice.

Practical Usage / Commands / Code:
    int <left_ptr> = 0, <right_ptr> = 0;
    long long <current_window_sum> = 0;
    int <max_length> = 0;

    while (<right_ptr> < <array>.size()) {
        // 1. Expand window
        <current_window_sum> += <array>[<right_ptr>];

        // 2. Shrink window if invalid (e.g., exceeded target)
        while (<current_window_sum> > <target> && <left_ptr> <= <right_ptr>) {
            <current_window_sum> -= <array>[<left_ptr>];
            <left_ptr>++;
        }

        // 3. Check condition and process valid window
        if (<current_window_sum> == <target>) {
            <max_length> = max(<max_length>, <right_ptr> - <left_ptr> + 1);
        }
        <right_ptr>++;
    }

Operations / Best Practices:
    - Prefix Sum Variant    // Subarray sum can also be evaluated via [right] - [left - 1].
    - Handle Negatives      // Standard sliding window assumes positive values; if negatives exist, use a hash map.

*/

// ════════════════════════════════════════════════════════════════════════
// [03] BINARY SEARCH 
// ════════════════════════════════════════════════════════════════════════
/*
── Core Concept & Manual Implementation ────────────────────────
A divide-and-conquer algorithm that finds a target in a sorted collection by repeatedly halving the search space.

Key Notes:
    - The collection MUST be sorted before searching.
    - Primarily used for finding exact values, minimums, or maximums.
    - Time Complexity: O(log N).
    - Space Complexity: O(1) iterative, O(log N) recursive.

Practical Usage / Commands / Code:
    int binarySearch(const vector& arrayName, dataType targetValue) {
        int leftPtr = 0;
        int rightPtr = arrayName.size() - 1;
        while (leftPtr <= rightPtr) {
            // Prevents integer overflow:
            int midPtr = leftPtr + (rightPtr - leftPtr) / 2; 
            
            if (arrayName[midPtr] == targetValue) return midPtr;
            if (arrayName[midPtr] < targetValue) leftPtr = midPtr + 1;
            else rightPtr = midPtr - 1;
        }
        return -1;
    }

Operations / Best Practices:
    - leftPtr <= rightPtr                // Use <= to ensure single-element intervals are checked
    - leftPtr + (rightPtr - leftPtr) / 2 // Always calculate mid this way to avoid integer overflow
    - return -1                          // Standard sentinel value indicating "not found"

── Binary Search on Range ─────────────────────────────────
Instead of searching an array, 
search a monotonic range of possible valid answers using a predicate function.

Key Notes:
    - Requires a boolean `isValid(mid)` function that evaluates if a state is possible.
    - The solution space must be monotonic (e.g., F F F T T T or T T T F F F).
    - Time Complexity: O(log(Search Space) * O(Predicate Function)).

Practical Usage / Commands / Code:
    bool isValid(int midValue, int targetCondition) {
        // Evaluates if midValue satisfies the specific problem conditions
        return currentAccumulation >= targetCondition;
    }

    int searchAnswer(int minLimit, int maxLimit, int targetCondition) {
        int leftPtr = minLimit, rightPtr = maxLimit, bestAnswer = maxLimit;
        
        while (leftPtr <= rightPtr) {
            int midPtr = leftPtr + (rightPtr - leftPtr) / 2;
            
            if (isValid(midPtr, targetCondition)) {
                bestAnswer = midPtr;         // Record valid answer
                rightPtr = midPtr - 1;       // Try to find a smaller/better answer
            } else {
                leftPtr = midPtr + 1;        // Increase to meet conditions
            }
        }
        return bestAnswer;
    }

Operations / Best Practices:
    - bestAnswer = midPtr // Always save the valid mid state before moving pointers
    - rightPtr = mid - 1  // Adjust bounds based on whether you need the minimum or maximum valid answer

── Binary Search on Doubles Range (Floating-Point) ───────────────────
Binary search adapted for continuous values (e.g., long double) rather than discrete integers.

Key Notes:
    - Avoid standard `left <= right` because precision limits can cause infinite loops.
    - Iterate a fixed number of times (e.g., 100-300) for guaranteed precision and termination.
    - Do NOT use `mid + 1` or `mid - 1`; bounds update directly to `mid`.

Practical Usage / Commands / Code:
    bool isValidDouble(double midValue, const vector& arrayName) {
        // Continuous evaluation logic
        return checkCondition;
    }

    double searchDoubleAnswer(double minLimit, double maxLimit, const vector<double>& arrayName) {
        double leftPtr = minLimit, rightPtr = maxLimit, bestAnswer = minLimit;
        int iterations = 300; // Fixed iterations for high precision (e.g., 10^-9)
        
        while (leftPtr <= rightPtr && iterations--) {
            double midPtr = leftPtr + (rightPtr - leftPtr) / 2.0;
            
            if (isValidDouble(midPtr, arrayName)) {
                bestAnswer = midPtr;
                leftPtr = midPtr;    // Update directly to mid (NO +/- 1)
            } else {
                rightPtr = midPtr;   // Update directly to mid (NO +/- 1)
            }
        }
        return bestAnswer;
    }

Operations / Best Practices:
    - int iterations = 300 // Runs in O(1) loop operations but secures extreme precision safely
    - leftPtr = midPtr     // Floating point bounds shift exactly to mid, preventing skipping valid decimals

── Virtual 1D Array Mapping ─────────────────────────────────────
Treats a row-major sorted M x N matrix as a virtual 1D array of size M * N. 
Converts a 1D mid-index back into 2D row/col coordinates using basic division and modulo operations.

Key Notes:
    - Time Complexity: O(log(M * N))
    - Space Complexity: O(1) auxiliary space
    - Row Index Formula: row = mid / cols
    - Column Index Formula: col = mid % cols
    - Precondition: Each row must be sorted, and the first element 
                    of each row must be greater than the last element of the previous row

Practical Usage / Code:
    bool searchMatrix(const vector<vector>& MatrixName, int TargetValue) {
        int rows = MatrixName.size(), cols = MatrixName[0].size();
        int left = 0, right = (rows * cols) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / cols, col = mid % cols;
            int currentVal = MatrixName[row][col];

            if (currentVal == TargetValue)
                return true;
            else if (TargetValue < currentVal)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return false;
    }
Operations / Best Practices:
    - Index Mapping       // Use mid / cols to get row and mid % cols to get column
    - Avoid Overflow      // Use left + (right - left) / 2 or midpoint(left, right)
    - Edge Validation     // Ensure matrix is non-empty (rows > 0 && cols > 0) prior to indexing

── STL Algorithms () ────────────────────────────────
C++ standard library functions that perform binary search operations on sorted ranges using iterators.

Key Notes:
    - Requires `#include <algorithm>`.
    - Time Complexity: O(log N) for random-access iterators (like vector).
    - Can accept custom comparator functions as an optional last argument.

Practical Usage / Commands / Code:
    // 1. Check if element exists (returns bool)
    bool isFound = binary_search(containerName.begin(), containerName.end(), targetValue);

    // 2. Find first element >= target (returns iterator)
    auto lowerItr = lower_bound(containerName.begin(), containerName.end(), targetValue);
    
    // 3. Find first element > target (returns iterator)
    auto upperItr = upper_bound(containerName.begin(), containerName.end(), targetValue);

Operations / Best Practices:
    - distance(containerName.begin(), itrName)  // Gets the integer index from the returned iterator
    - itrName - containerName.begin()                // Alternative, faster index extraction for vectors
    - itrName != containerName.end()                 // Verifies exact match when using lower_bound
    - sort(containerName.begin(), containerName.end()) // Ensure collection is sorted beforehand
*/

