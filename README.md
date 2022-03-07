# 2010

A Clash of Titans: Randomized vs. Deterministic

This program compares the runtimes of two implementations of the quick select algorithm.
The goal of the algorithm is, provided an unsorted array and a rank (k-th smallest position) in said array, return the position (or value) of said element.
Both algorithms extend the classic quick-sort algorithm by applying prune-and-search techniques.
The key difference between each is how we chose a pivot for partitioning the sub-arrays. 
Randomized Select -- as implied -- choses a pivot at random. Whereas Deterministic Select choses a pivot by approximating the median of the array.

To run in command line:
- go to file directory
- g++ deterministic-select.cpp -o run
- ./run
- Input _Size_ of randomly generated array
- Input number of _Attempts_ (or iterations) to determine average / worst number of comparisons
