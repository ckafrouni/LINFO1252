# Common Sorting Algorithms

### This folder implements common sorting algorithms.

|   Algorithm    | Time Complexity | Space Complexity | Stable | In-Place |
| :------------: | :-------------: | :--------------: | :----: | :------: |
| Selection Sort |     O(n^2)      |       O(1)       |   ⛔    |    ✅     |
| Insertion Sort |     O(n^2)      |       O(1)       |   ✅    |    ✅     |
|   Merge Sort   |    O(nlogn)     |       O(n)       |   ✅    |    ⛔     |
|   Quick Sort   |    O(nlogn)     |       O(1)       |   ⛔    |    ✅     |
|   Shell Sort   |    O(nlogn)     |       O(1)       |   ⛔    |    ✅     |
|  Bubble Sort   |     O(n^2)      |       O(1)       |   ✅    |    ✅     |

* **Stable**: If two elements with equal values appear in the same order in the sorted output as they appear in the input array.
* **In-Place**: If the algorithm does not use extra space for manipulating the input but may require a small amount of extra space for its operation.

### Selection Sort
    - Find the smallest element in the unsorted array and swap it with the element at the beginning.
    - Repeat the above process for all the elements until the entire array is sorted.

### Insertion Sort
    - Iterate from arr[1] to arr[n] over the array.
    - Compare the current element (key) to its predecessor.
    - If the key element is smaller than its predecessor, compare it to the elements before.
    - Move the greater elements one position up to make space for the swapped element.

### Merge Sort (Divide and Conquer)
    - Divide the unsorted array into n subarrays, each containing 1 element (a list of 1 element is considered sorted).
    - Repeatedly merge subarrays to produce new sorted subarrays until there is only 1 subarray remaining.

### Quick Sort (Divide and Conquer)
    - Pick an element as pivot and partition the given array around the picked pivot.
    - Partitioning: reorder the array so that all elements with values less than the pivot come before the pivot, while all elements with values greater than the pivot come after it.
    - After partitioning, the pivot is in its final position.
    - Recursively apply the above steps to the subarray of elements with smaller values and separately to the subarray of elements with greater values.

### Shell Sort (Insertion Sort with Gap)
    - Start with a large gap, then reduce the gap until it becomes 1.
    - Perform insertion sort for elements at a specific gap.
    - The final insertion sort will be a normal insertion sort but with a small amount of data.

### Bubble Sort
    - Repeatedly swap adjacent elements if they are in wrong order.
    - The pass through the list is repeated until the list is sorted.
    - The algorithm gets its name from the way smaller or larger elements "bubble" to the top of the list.
  