# Common Sorting Algorithms

## Overview

This repository contains implementations of common sorting algorithms, along with their characteristics such as time complexity, space complexity, stability, and whether they are in-place algorithms.

|   Algorithm    | Best-Case Time Complexity | Worst-Case Time Complexity | Space Complexity | Stable | In-Place |
| :------------: | :-----------------------: | :------------------------: | :--------------: | :----: | :------: |
| Selection Sort |          \(O(n^2)\)       |          \(O(n^2)\)        |       \(O(1)\)   |   ⛔    |    ✅     |
| Insertion Sort |          \(O(n)\)         |          \(O(n^2)\)        |       \(O(1)\)   |   ✅    |    ✅     |
|  Bubble Sort   |          \(O(n)\)         |          \(O(n^2)\)        |       \(O(1)\)   |   ✅    |    ✅     |
|   Merge Sort   |         \(O(n\log n)\)    |         \(O(n\log n)\)     |       \(O(n)\)   |   ✅    |    ⛔*    |
|   Quick Sort   |         \(O(n\log n)\)    |          \(O(n^2)\)        |       \(O(1)\)   |   ⛔*   |    ✅     |
|   Shell Sort   |    Depends on Gap Sequence |    Depends on Gap Sequence |       \(O(1)\)   |   ⛔    |    ✅     |

\* Quick Sort can be made stable with modifications.  
\* In-place versions of Merge Sort exist but are less common.

### Key Terms

- **Stable**: A sorting algorithm is stable if two elements with equal values appear in the same order in the sorted output as they do in the input array.
- **In-Place**: A sorting algorithm is in-place if it doesn't use extra space for manipulating the input, although it may require a small amount of extra memory for its operation.

## Algorithm Descriptions

### Selection Sort
- Find the smallest element in the unsorted array and swap it with the element at the beginning.
- Repeat the above process for each remaining unsorted element until the entire array is sorted.

### Insertion Sort
- Iterate from `arr[1]` to `arr[n]` over the array.
- Compare the current element (key) to its predecessor.
- If the key element is smaller than its predecessor, compare it to the elements before it.
- Move the greater elements one position up to make space for the swapped element.

### Bubble Sort
- Repeatedly swap adjacent elements if they are in the wrong order.
- Continue this process until the list is sorted.
- The algorithm gets its name from the way smaller or larger elements "bubble" to the top of the list.

### Merge Sort (Divide and Conquer)
- Divide the unsorted array into \(n\) sub-arrays, each containing 1 element (a list of 1 element is considered sorted).
- Repeatedly merge sub-arrays to produce new sorted sub-arrays until there is only 1 sub-array remaining.

### Quick Sort (Divide and Conquer)
- Pick an element as a pivot and partition the given array around the picked pivot.
- Reorder the array so that all elements with values less than the pivot come before the pivot, while all elements with values greater than the pivot come after it.
- Recursively apply the above steps to the sub-array of elements with smaller values and separately to the sub-array of elements with greater values.

### Shell Sort (Generalized Insertion Sort)
- Start with a large gap and reduce the gap in each iteration.
- Perform insertion sort for elements at each specific gap.
- The final insertion sort will be a normal insertion sort but with a smaller amount of data.

## Algorithms Ordered by Implementation Complexity (General Guideline)
- Bubble Sort
- Selection Sort
- Insertion Sort
- Shell Sort
- Merge Sort
- Quick Sort

## TODO Checklist for Implementation

- [x] [Bubble Sort](./bubblesort.c)
- [x] [Selection Sort](./selectionsort.c)
- [ ] [Insertion Sort](./insertionsort.c)
- [ ] [Shell Sort](./shellsort.c)
- [ ] [Merge Sort](./mergesort.c)
- [x] [Quick Sort](./quicksort.c)