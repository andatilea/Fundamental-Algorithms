// HEAP SORT

//Heap sort is similar to SelectionSort where we first find the maximum element and place it at the end;
//One of its advantages is the runtime during the worst case: O(nlogn);

// - first way of building the heap: BOTTOM UP
// - second way of building the heap: TOP DOWN

//BOTTOM UP:
// - Bottom-up heapsort reduces the number of comparisons;
// - The ordinary heapsort requires two comparisons, to find the minimum of three elements: the new node and its children;
// - Meanwhile, bottom up heap sort uses only one comparison per level;
// - how it works: it builds a heap from the bottom up by sifting downward;
// - All the parents are greater than their siblings;

//TOP DOWN:
// - Extracts the element on the top of the heap;
// - It shifts the next element down the heap (this element comes from the lowest level, so it is one of the smallest);
// - Top-down heapsort requires more steps;
// - Top-down uses a recursive call;
// - Top-down presents more operations;
// - how it works: it builds a heap top down by sifting upward;


//COMPARISON
// - The Bottom-up method uses only n/2 elements, meanwhile Top-down method uses n elements;
// - Top-down requires more steps(operations);
// - Bottom-Up method has O(n) time complexity, meanwhile the Top-Down method has O(nlogn) time complexity;

#include <stdio.h>
#include<iostream>
#include "Profiler.h"

using namespace std;
Profiler profiler("heap-sort");

#define SIZE 5
#define I 100
#define MAX 10000

int bottom_up_asign;
int bottom_up_comp;
int bottom_up_totalOp;

int top_down_asign;
int top_down_comp;
int top_down_totalOp;

void swap(int* x, int* y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}

// print the array;
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//BOTTOM-UP

void heapify_bottom_up(int arr[], int n, int i)
{
	// the largest item is the root;
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// if left child is larger;
	bottom_up_comp++;
	if (left < n && arr[largest] < arr[left])
	{
		largest = left;
	}
	// if right child is larger;

	bottom_up_comp++;
	if (right < n && arr[largest] < arr[right])
	{
		largest = right;
	}
	// if one of the children is larger we need to swap in order to get the largest at the top;

	// if largest term is not the root;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		bottom_up_asign += 3;
		heapify_bottom_up(arr, n, largest);

	}
}

// algorithm to build a heap
void build_heap_bottom_up(int arr[], int n)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		heapify_bottom_up(arr, n, i);
	}
}


//HEAPSORT

void heapsort(int arr[], int n)
{
	build_heap_bottom_up(arr, n);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);

		//heapify the reduced heap;
		heapify_bottom_up(arr, i, 0);
	}
}

//TOP-DOWN

void recursive(int arr[], int i)
{
	//the top-down method requires a recursive call(the function calls itself);
	top_down_totalOp++;
	if(i!=0)
	{
		int parent = (i - 1) / 2;
		top_down_comp++;
		if (arr[parent] < arr[i])
		{
			swap(arr[i], arr[parent]);
			top_down_asign += 3;
			recursive(arr, parent);
		}
	}
}

void push(int* arr, int &index, int key)
{

	index++;
	int current_position = index;

	arr[current_position] = key;
	top_down_comp++;

	while ((current_position > 0) && (arr[(current_position - 1) / 2] < arr[current_position]))
	{
		top_down_comp ++;
		swap(arr[current_position], arr[(current_position - 1) / 2]);
		top_down_asign += 3;

		current_position = (current_position - 1) / 2;
	}
}

int *build_heap_top_down(int arr[], int n)
{

	int* result = (int*)malloc(n * sizeof(int));
	int flag = 0;

	// increase heap for every step
	for (int size = 1; size < n; size++)
	{
		push(result,flag,arr[size]);
	}
	return result;
}

//DEMOS

void build_heap_bottom_up_demo(int arr[], int n)
{
	int i;
	for (i = (n / 2) - 1; i >= 0; i--)
	{
		heapify_bottom_up(arr, n, i);
		printf("\n%d: ", n - n / 2 - i);
		printArray(arr, n);
	}
}
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


void build_heap_top_down_demo(int arr[], int n)
{
	// increase heap for every step
	for (int size = 1; size < n; size++)
	{
		printf("\n%d: ", size);
		printArray(arr, n);
		recursive(arr, size);
	}
}


void building_heap_average_case(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		top_down_asign = 0;
		top_down_comp = 0;

		bottom_up_asign = 0;
		bottom_up_comp = 0;

		for (int i = 0; i < 5; i++)
		{
			int* a = (int*)malloc(n * sizeof(int));
			int* b = (int*)malloc(n * sizeof(int));
			FillRandomArray(a, n);
			CopyArray(b, a, n);

			build_heap_bottom_up(a, n);
			build_heap_top_down(b, n);
		}

		profiler.countOperation("Average_bottom_up_totalOp", n, bottom_up_asign + bottom_up_comp);
		profiler.countOperation("Average_top_down_totalOp", n, top_down_asign + top_down_comp);

	}
}
int main()
{
	int a[SIZE];
	int b[SIZE], c[SIZE];
	FillRandomArray(a, SIZE);
	CopyArray(b, a, SIZE);
	CopyArray(c, a, SIZE);

	//bottom up demo
	printf("\n DEMO Bottom Up: \n");
	printArray(a, SIZE);
	build_heap_bottom_up_demo(a, SIZE);
	printArray(a, SIZE);


	//heapsort demo
	printf("\n DEMO HeapSort:\n");
	printArray(c, SIZE);
	heapsort_demo(c, SIZE);
	printArray(c, SIZE);


	//top down demo
	printf("\n DEMO Top Down\n");
	printArray(b, SIZE);
	build_heap_top_down_demo(b, SIZE);
	printArray(b, SIZE);


	building_heap_average_case(I, MAX);
	profiler.createGroup("Bottom-Up vs Top-Down:Average", "Average_bottom_up_totalOp", "Average_top_down_totalOp");

	profiler.showReport();
	system("pause");
	return 0;
}

