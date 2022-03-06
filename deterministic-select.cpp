/*
** select.cpp
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>

/* 
** generateVector - this function fills a vector with random numbers
*/
std::vector<int> generateVector(int size) 
{
    std::vector<int> v(size);

    for(int i = 0; i < size; i++) {
	v.at(i) = rand() % (100 * size);
    }
    return v;
}

/*
** insertionSort -  use the insertionSort algorithm that sorts the portion
** vector[first ... last] of vector and updates the number of comparisons made.
*/
template <class type>
void insertionSort(std::vector<type>& v, int first, int last, int &comparisons)
{
    for (int i = first + 1; i <= last; i++)
    {
        int index = i-1;
	type elem = v.at(i);

	/*
	** Move element "elem" into position within the part of v we care about.
	*/
        while (index >= first && elem < v.at(index))
	{
	    v.at(index + 1) = v.at(index);
	    comparisons++;
	    index--;
	}
	v.at(index+1) = elem;

	/*
	** Adjust the number of comparisons.
	*/
	if (index >= first)
	{
	    comparisons++;
	}
    }
}

/*
** A simple swap function.
*/
template<class type>
void swap(type& a, type& b)
{
    type tmp = a;
    a = b;
    b = tmp;
}

/*
** Now  the partition algorithm  of  quicksort, modified  to (1) count the
** number of comparisons it  is making and  (2) take as an extra parameter
** the position of the pivot to be used.
**
** This algorithm computes the Lesser and Greater vectors from our pseudo-
** code as follows: it moves the elements in vector[first ... last] so
** Lesser = vector[first ... mid-1], Greater = vector[mid+1 ... last] and
** the pivot is A[mid]. The function returns the position "mid".
*/
template<class type>
int partition(std::vector<type>&v, int first, int last, int pivotPosition, int &comparisons)
{
    swap(v.at(pivotPosition), v.at(last));
    type pivot = v.at(last);
    int back = first - 1;

    for (int front = first; front < last; front++)
    {
	comparisons++;
	if (v.at(front) <= pivot)
	{
	    back++;
	    swap(v.at(front), v.at(back)); 
	}
    }

    swap(v.at(back+1), v.at(last));
    return back+1;
}

/*
** print - function to print a vector (useful for debugging)
*/
template<class type>
void print(const std::vector<type>& v)
{
    for (unsigned int counter = 0; counter < v.size(); counter++) {
	std::cout << v.at(counter) << " ";
    }
    std::cout << std::endl;
}

/*
** Randomized function to  find the kth  smallest element of  a vector. It
** returns the position in the vector where the element was found.
*/

template<class type>
int randomizedQuickSelect(std::vector<type>& v, int first, int last, int i, int &comparisons)
{
    if (last > 1) {

        int pivot = rand() % (last - first + 1);
        int mid = partition(v, first, last, pivot, comparisons);
        int sizeOfLesser = mid - 1;

        if (sizeOfLesser == i-1) return mid;
        else {
            if (sizeOfLesser > i-1) {
                return randomizedQuickSelect(v, first, mid-1, i, comparisons);
            } else {
                int k = i - sizeOfLesser - 1;
                return randomizedQuickSelect(v, mid+1, last, k, comparisons);
            }
        }
    } else {
        return first;
    }
}
    
/*
** Now the deterministic selection algorithm.
**
*/
template<class type>
int select(std::vector<type>& v, int first, int last, int i, int &comparisons)
{
    if (last >= 5) {

        int numGroups = floor(last / 5);
        std::vector<int> medians(numGroups);

        for (int j = 0; j < numGroups; j++) {
            int currFirst = 5*j;
            int currLast = (5*j + 5) - 1;
            insertionSort(v, currFirst, currLast, comparisons);
            int pos = 5*j + 2;
            medians[i] = v[pos];
        }

        insertionSort(medians, 0, numGroups, comparisons);
        int mid = medians[numGroups/2];

        int sizeOfLesser = mid - 1;

        if (sizeOfLesser == i-1) return mid;
        else {
            if (sizeOfLesser > i-1) {
                return select(v, first, mid-1, i, comparisons);
            } else {
                int k = i - sizeOfLesser - 1;
                return select(v, mid+1, last, k, comparisons);
            }
        }
    } else {
        insertionSort(v, first, last, comparisons);
        return v[i-1];
    }
}

/*
 * runtests method/function should read in two parameters size and attempts, generate attempts
 * random arrays of length size, and for each array find the median using both of the algorithms you
 * need to implement. It should then print
 *    • the average number of comparisons made over all attempts, and
 *    • the worst-case number of comparisons made over all attempts.
*/
void runtests() 
{
    std::cout << std::endl;
    std::cout << "Size: ";
    int size;
    std::cin >> size;
    std::cout << "Attempts: ";
    int attempts;
    std::cin >> attempts;

    int median = size/2;

    int rqsTotal;
    int dsTotal;
    int rqsWorst = 0;
    int dsWorst = 0;

    for (int i = 0; i < attempts; i++) {
        std::vector<int> v = generateVector(size);

        int rqsCurr = 0;
        int dsCurr = 0;

        int rqsOut = randomizedQuickSelect(v, 0, size-1, median, rqsCurr);
        rqsTotal += rqsCurr;
        if (rqsCurr > rqsWorst) rqsWorst = rqsCurr;

        int dsOut = select(v, 0, size-1, median, dsCurr);
        dsTotal += dsCurr;
        if (dsCurr > dsWorst) dsWorst = dsCurr;

        assert(v[rqsOut] == v[dsOut]);

        std::vector<int> sorted = generateVector(size);
        insertionSort(sorted, 0, size-1, rqsCurr);
        std::cout << "original: ";
        print(v);
        std::cout << "sorted: ";
        print(sorted);
        std::cout << "median RQS: " << v[rqsOut] << std::endl;
        std::cout << "median DS: " << v[dsOut] << std::endl;
        std::cout << "median Actual: " << sorted[median] << std::endl;
    }

    int rqsAvg = rqsTotal / attempts;
    int dsAvg = dsTotal / attempts;

    std::cout << std::endl;
    std::cout << "--Results for Randomized Quick Select--" << std::endl;
    std::cout << "Average Comparison: " << rqsAvg << std::endl;
    std::cout << "Worst Comparison: " << rqsWorst << std::endl;
    std::cout << std::endl;
    std::cout << "--Results for Deterministic Select--" << std::endl;
    std::cout << "Average Comparison: " << dsAvg << std::endl;
    std::cout << "Worst Comparison: " << dsWorst << std::endl;
    std::cout << std::endl;
}

int main()
{
    runtests();
}
