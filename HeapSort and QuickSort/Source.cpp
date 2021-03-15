//QUICKSORT 
//The algorithm sorts n numbers, its worst running time is O(n^2) -  it occurs when one subarray contains(n-1) elements and the other one has 0 elements;
//Its expected(average) running time is O(nlgn);
//It is popular for sorting large input arrays;

//The algorithm applies the Divide and conquer paradigm;
	//Divide: Partition(rearrange) the array into 2 subarrays;
	//Conquer: sort the 2 subarrays by using recursive calls;
	//Combine: re-create the total array;

//The BEST Case of the algorithm is very similar to the Average Case;
//How the PARTITION works: we have an array and an element p (pivot) contained in the array;
			// we have to put x in its correct position in the sorted array;
			// all smaller elements will be placed before x, all larger elements will be placed after x;
			// we start from the leftmost element and perform the swap when needed;


		//HEAPSORT
//Heap sort is similar to SelectionSort where we first find the maximum element and place it at the end;
//One of its advantages is the runtime during the worst case: O(nlogn);
// - Bottom-up heapsort reduces the number of comparisons;
// - how it works: it builds a heap from the bottom up by sifting downward;
// - All the parents are greater than their siblings;

//COMPARISON QuickSort vs. HeapSort:
		// - If we consider the worst case in time complexity, heapsort is better than quicksort;
		// - Otherwise, QuickSort is usually chosen;
		// - Both algorithms need the swap function;
		// - The partition in QuickSort represents the heapify in HeapSort;
		// - In QuickSort the next thing to be accessed is close to the element we analyze at the moment; HeapSort jumps significantly more;
		// - QuickSort is faster;

		//QUICKSELECT
//It represents a randomized QuickSort;
//We randomly chose the pivot element;
//In the new partition we simply implement the swap before actually partitioning;

//COMPARISON QuickSort vs. QuickSelect:
		// - the procedures only differ in how they select the pivot elements;
		// - the pivot is never included in any future recursive calls;


#include <stdio.h>
#include "Profiler.h"

#define SIZE 10
#define I 100
#define MAX 10000

using namespace std;
Profiler profiler("QuickSort");

int quicksort_totalOp;
int heapsort_asign;
int heapsort_comp;

//UTILITY FUNCTIONS
void swap(int* x, int* y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

//QUICKSORT
//lomuto method
//This function takes the last element as pivot, places it at its correct position in the sorted array;
//It places all smaller elements to the left and all greater elements to the right;
int partition(int arr[], int l, int r)
{
	quicksort_totalOp++; //asign

	int p = arr[r];
	int i = l - 1;
	int j;

	for (j = l; j < r; j++)
	{
		quicksort_totalOp++;  //comp

		if (arr[j] <= p)
		{
			i++;
			swap(arr[i], arr[j]);
			quicksort_totalOp += 3; //3 asign
		}
	}

	swap(arr[i + 1], arr[r]);
	quicksort_totalOp += 3;		//3 asign

	return i + 1;
}
// l- reperesents the starting index;
// r- represents the ending index;
void QuickSort(int arr[], int l, int r)
{
	if (l < r)
	{
		//it is now at its correct position;
		int quicksort = partition(arr, l, r);

		//sort elements before partition;
		QuickSort(arr, l, quicksort - 1);
		//sort elements after partition;
		QuickSort(arr, quicksort + 1, r);

	}
}
//HEAPSORT

//algorithm for Heapify
void heapify_bottom_up(int arr[], int n, int i)
{
	// the largest item is the root;
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	heapsort_comp++;
	// if left child is larger;
	if (left < n && arr[largest] < arr[left])
	{
		largest = left;
	}
	heapsort_comp++;
	// if right child is larger;
	if (right < n && arr[largest] < arr[right])
	{
		largest = right;
	}
	// if one of the children is larger we need to swap in order to get the largest at the top;

	// if largest term is not the root;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapsort_asign += 3;

		heapify_bottom_up(arr, n, largest);
	}
}

//algorithm to build a heap
void build_heap_bottom_up(int arr[], int n)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		heapify_bottom_up(arr, n, i);
	}
}

//heapsort algorithm
void heapsort(int arr[], int n)
{
	build_heap_bottom_up(arr, n);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapsort_asign += 3;

		heapify_bottom_up(arr, i, 0);
	}
}

//GRAPHS
void AVERAGE(int i, int max)
{
	for (int n = i; n <= max; n += i)
	{
		heapsort_asign = 0;
		heapsort_comp = 0;
		quicksort_totalOp = 0;

		for (int j = 0; j < 5; j++)
		{
			int* a = (int*)malloc(n * sizeof(int));
			int* b = (int*)malloc(n * sizeof(int));

			FillRandomArray(a, n);
			CopyArray(b, a, n);

			heapsort(a, n);
			QuickSort(b, 0, n - 1);
			free(a);
			free(b);
		}

		profiler.countOperation("HeapSort_AVERAGE_Case", n, heapsort_asign + heapsort_comp);
		profiler.countOperation("QuickSort_AVERAGE_Case", n, quicksort_totalOp);

	}
}

void BEST(int i, int max)
{
	for (int n = 0; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		quicksort_totalOp = 0;
		QuickSort(a, 0, n - 1);

		profiler.countOperation("QuickSort_BEST_Case", n, quicksort_totalOp);
		free(a);
	}
}


void WORST(int i, int max)
{
	for (int n = 0; n <= max; n += i)
	{
		int* b = (int*)malloc(n * sizeof(int));
		FillRandomArray(b, n, 10, 50000, false, 2);
		quicksort_totalOp = 0;
		QuickSort(b, 0, n - 1);

		profiler.countOperation("QuickSort_WORST_Case", n, quicksort_totalOp);
		free(b);
	}
}




//QUICKSELECT
//random pivot

int Random(int a, int b)
{
	return a + rand() % (b - a);
}

int partition_r(int arr[], int l, int r)
{
	int random = l + rand() % (r - l);
	swap(arr[random], arr[r]);

	return partition(arr, l, r);

}

void QuickSelect(int arr[], int l, int r)
{
	if (l < r)
	{
		int p = partition_r(arr, l, r);
		QuickSelect(arr, l, p - 1);
		QuickSelect(arr, p + 1, r);
	}
}



//DEMOS

//the demo for the partition
int partition_demo(int arr[], int l, int r)
{
	static int t = 1;
	printf(" %d:  ", t);
	printArray(arr, SIZE);
	printf("\n");
	t++;

	int p = arr[r];
	int i = l - 1;
	int j;

	for (j = l; j < r; j++)
	{
		if (arr[j] <= p)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[r]);

	return i + 1;
}

//the demo for the quicksort algorithm
void QuickSort_demo(int arr[], int l, int r)
{
	if (l < r)
	{
		int quicksort = partition_demo(arr, l, r);
		QuickSort_demo(arr, l, quicksort - 1);
		QuickSort_demo(arr, quicksort + 1, r);
	}
}

//quickselect demos
int partition_random_demo(int arr[], int l, int r)
{
	static int step = 1;
	printf(" %d: ", step);
	printArray(arr, SIZE);
	printf("\n");
	step++;

	int random = l + rand() % (r - l);
	swap(arr[random], arr[r]);

	return partition(arr, l, r);
}

void QuickSelect_demo(int arr[], int l, int r)
{
	if (l < r)
	{
		int p = partition_random_demo(arr, l, r);
		QuickSelect_demo(arr, l, p - 1);
		QuickSelect_demo(arr, p + 1, r);
	}
}

//HEAPSORT demo
void heapsort_demo(int arr[], int n)
{
	build_heap_bottom_up(arr, n);
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		printf("\n%d: ", SIZE - i);
		printArray(arr, SIZE);

		swap(arr[0], arr[i]);


		heapify_bottom_up(arr, i, 0);
	}

	printf("\n%d: ", SIZE - i);
	printArray(arr, SIZE);
}


int main()
{
	int arr[] = { 10,23,31, 5,7,9, 12, 30,15,62 };
	int brr[SIZE];
	int c[SIZE];
	//FillRandomArray(arr, SIZE);
	CopyArray(brr, arr, SIZE);
	CopyArray(c, arr, SIZE);

	// demo QuickSort
	printf("\n*********************** QUICK SORT starts ****************************\n");
	printf("\nBefore:  ");
	printArray(arr, SIZE);
	printf("\n");

	QuickSort_demo(arr, 0, SIZE - 1);
	printf("After:  ");
	printArray(arr, SIZE);
	printf("\n*********************** QUICK SORT ends ****************************\n");
	printf("\n");


	//demo QuickSelect
	printf("\n*********************** QUICK SELECT starts ****************************\n");
	printf("\nBefore:  ");
	printArray(brr, SIZE);
	printf("\n");

	QuickSelect_demo(brr, 0, SIZE - 1);
	printf("After:  ");
	printArray(brr, SIZE);
	printf("\n*********************** QUICK SELECT ends ****************************\n");
	printf("\n");


	// demo HeapSort
	printf("\n*********************** HEAP SORT starts ****************************\n");
	printf("\nBefore:  ");
	printArray(c, SIZE);
	heapsort_demo(c, SIZE);
	printf("\nAfter:  ");
	printArray(c, SIZE);
	printf("\n*********************** HEAP SORT ends ****************************\n");
	printf("\n");


	//AVERAGE Case
	AVERAGE(I, MAX);
	profiler.createGroup("HeapSort_vs_QuickSort_Average_Case", "HeapSort_AVERAGE_Case", "QuickSort_AVERAGE_Case");

	//BEST Case
	BEST(I, MAX);


	//WORST Case
	WORST(I, MAX);

	profiler.showReport();
	return 0;
}
