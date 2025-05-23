The Programming Assignments of Algorithms by Prof. Yao-Wen Chang, Fall 2024

## PA1: Sorting
Implementing and analyzing different sorting algorithms, including:
- Insertion sort
- Merge sort
- Bottom-up Merge sort
- Quick sort
- Randomized quick sort
- Heap sort

## PA2: Dynamic Programming
Use dynamic programming to solve the [**Maximum Planar Subset problem**](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=1270250), which can be transformed into a graph problem.
Remark: My implementation works for at least 20000 points, but it cannot pass the 60000-point sample input given by the TAs.

## PA3: Graph - Cycle Breaking
Given a simple, weighted (may be either directed or undirected) graph $G = (V, E, w)$, the cycle breaking problem is to make G *acyclic* by removing some edges in $E$ such that the total weight of the removed edges is minimized.
