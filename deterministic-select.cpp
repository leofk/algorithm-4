/*
** select.cpp
*/

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

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
    return 0;
}
    
/*
** Now the deterministic selection algorithm.
**
*/
template<class type>
int select(std::vector<type>& v, int first, int last, int i, int &comparisons)
{
    return 0;
}

/*
** Method runtests is really our main.
 * Your runtests method/function should read in two parameters size and attempts, generate attempts
 * random arrays of length size, and for each array find the median using both of the algorithms you
 * need to implement. It should then print
 *    • the average number of comparisons made over all attempts, and
 *    • the worst-case number of comparisons made over all attempts.
*/
void runtests() 
{
    cout << endl;
    cout << "Size: ";
    int size;
    cin >> size;
    cout << "Attempts: ";
    int attempts;
    cin >> attempts;

    int median = size/2;

    int rqsTotal;
    int dsTotal;
    int rqsWorst = 0;
    int dsWorst = 0;

    for (int i = 0; i < attempts; i++) {
        vector<int> v = generateVector(size);

        int rqsCurr = 0;
        int dsCurr = 0;

        int rqsOut = randomizedQuickSelect(v, 0, size-1, median, rqsCurr);
        rqsTotal += rqsCurr;
        if (rqsCurr > rqsWorst) rqsWorst = rqsCurr;

        int dsOut = select(v, 0, size-1, median, dsCurr);
        dsTotal += dsCurr;
        if (dsCurr > dsWorst) dsWorst = dsCurr;

        assert(v[rqsOut] == v[dsOut]);
    }

    int rqsAvg = rqsTotal / attempts;
    int dsAvg = dsTotal / attempts;

    cout << endl;
    cout << "--Results for Randomized Quick Select--" << endl;
    cout << "Average Comparison: " << rqsAvg << endl;
    cout << "Worst Comparison: " << rqsWorst << endl;
    cout << endl;
    cout << "--Results for Deterministic Select--" << endl;
    cout << "Average Comparison: " << dsAvg << endl;
    cout << "Worst Comparison: " << dsWorst << endl;
    cout << endl;
}

int main()
{
    runtests();

//  to run program in shell
//  g++ deterministic-select.cpp -o run
}
