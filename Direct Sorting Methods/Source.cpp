												//ALGORITHMS FOR SORTING

//BUBBLESORT:
//It swaps elements to get the smallest in the first position;
//O(n ^ 2) is the Average Case for BubbleSort Algorithm;
//O(n) is the Best Case for BubbleSort Algorithm;
//Also O(n^2) is the Worst Case for BubbleSort Algorithm;
//STABLE

//SELECTIONSORT:
//It selects the smallest element from the unsorted array and places it at the beginning of the list;
//O(n^2) in all three cases(Average, Best, Worst);
//Not STABLE (only with extra memory used);
//At each step we also use SWAP (simillar to BubbleSort) to take the smallest element and interchange it with element i+1;

//INSERTIONSORT:
//The first element in the array is said to be sorted; we take the following element and store it in aux;
//We compare the two of them. While the element > aux, then aux will be placed in front of the element (the sorted element will be moved to the right);
// We repeat this until every unsorted element is at the correct position;
//O(n^2) is the Average Case for InsertionSort Algorithm;
//O(n) is the Best Case for InsertionSort Algorithm;
//O(n^2) is the Worst Case for InsertionSort Algorithm;
//STABLE (because of the WHILE condition);

//GRAPHS
// BubbleSort (average, best, worst: for assign, comp, sumOp);
//SelectionSort(average, best, worst:for assign, comp, sumOp);
//InsertionSort(average, best, worst:for assign, comp, sumOp);

#include "Profiler.h"
#include <conio.h>
#include <stdio.h>

#define size 10

#define I 100
#define MAX 10000

Profiler profiler("Sorting Methods");

int comp_insertion, assign_insertion;
int comp_selection, assign_selection;
int comp_bubble, assign_bubble;

void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


// INSERTION SORT

void InsertionSort(int arr[], int n)
{

	int i, j, buf;
	for (i = 1; i < n; i++)
	{
		buf = arr[i];
		assign_insertion++;							
		j = i - 1;
		while (arr[j] > buf && j >= 0)
		{
			comp_insertion++;						
			arr[j + 1] = arr[j];
			assign_insertion++;						
			j = j - 1;
		}
		comp_insertion++;							
		arr[j + 1] = buf;
		assign_insertion++;							
	}
}

void best_case_insertion(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_insertion = 0;
		comp_insertion = 0;
		InsertionSort(a, n);

		profiler.countOperation("Best_Case_InsertionSort_assign", n, assign_insertion);
		profiler.countOperation("Best_Case_InsertionSort_comp", n, comp_insertion);

	}
	profiler.addSeries("Best_Case_InsertionSort_sumOp", "Best_Case_InsertionSort_assign", "Best_Case_InsertionSort_comp");
}

void worst_case_insertion(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_insertion = 0;
		comp_insertion = 0;
		InsertionSort(a, n);

		

		profiler.countOperation("Worst_Case_InsertionSort_assign", n, assign_insertion);
		profiler.countOperation("Worst_Case_InsertionSort_comp", n, comp_insertion);

	}
	profiler.addSeries("Worst_Case_InsertionSort_sumOp", "Worst_Case_InsertionSort_assign", "Worst_Case_InsertionSort_comp");
}


void average_case_insertion(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		assign_insertion = 0;
		comp_insertion = 0;
		for (int i = 0; i < 5; i++)
		{
			int* a = (int*)malloc(n * sizeof(int));
			FillRandomArray(a, n);
			InsertionSort(a, n);
		}
		assign_insertion /= 5;
		comp_insertion /= 5;
	

		profiler.countOperation("Average_Case_InsertionSort_assign", n, assign_insertion);
		profiler.countOperation("Average_Case_InsertionSort_comp", n, comp_insertion);

	}
	profiler.addSeries("Average_Case_InsertionSort_sumOp", "Average_Case_InsertionSort_assign", "Average_Case_InsertionSort_comp");
}



// BUBBLE SORT

void BubbleSort(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			comp_bubble++;				
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				assign_bubble += 3;		// 3 asign
			}
		}
	}
}

void best_case_bubble(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_bubble = 0;
		comp_bubble = 0;
		BubbleSort(a, n);

	

		profiler.countOperation("Best_Case_BubbleSort_assign", n, assign_bubble);
		profiler.countOperation("Best_Case_BubbleSort_comp", n, comp_bubble);

	}
	profiler.addSeries("Best_Case_BubbleSort_sumOp", "Best_Case_BubbleSort_assign", "Best_Case_BubbleSort_comp");
}

void worst_case_bubble(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_bubble = 0;
		comp_bubble = 0;
		BubbleSort(a, n);

		

		profiler.countOperation("Worst_Case_BubbleSort_aasign", n, assign_bubble);
		profiler.countOperation("Worst_Case_BubbleSort_comp", n, comp_bubble);

	}
	profiler.addSeries("Worst_Case_BubbleSort_sumOp", "Worst_Case_BubbleSort_assign", "Worst_Case_BubbleSort_comp");
}


void average_case_bubble(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		assign_bubble = 0;
		comp_bubble = 0;
		for (int i = 0; i < 5; i++)
		{
			int* a = (int*)malloc(n * sizeof(int));
			FillRandomArray(a, n);
			BubbleSort(a, n);
		}
		assign_bubble /= 5;
		comp_bubble /= 5;
	

		profiler.countOperation("Average_Case_BubbleSort_assign", n, assign_bubble);
		profiler.countOperation("Average_Case_BubbleSort_comp", n, comp_bubble);

	}
	profiler.addSeries("Average_Case_BubbleSort_sumOp", "Average_Case_BubbleSort_assign", "Average_Case_BubbleSort_comp");
}



// SELECTION SORT

void SelectionSort(int arr[], int n)
{
	int i, j, min, buff;
	for (i = 0; i < n - 1; i++)
	{
		min = i;

		for (j = i + 1; j < n; j++)
		{
			comp_selection++;
			if (arr[j] < arr[min]) 
				min = j;			
		}

		buff = arr[i];										// 3 asign
		arr[i] = arr[min];
		arr[min] = buff;
		assign_selection += 3;
	}
}

void best_case_selection(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_selection = 0;
		comp_selection = 0;
		SelectionSort(a, n);

	

		profiler.countOperation("Best_Case_SelectionSort_assign", n,assign_selection);
		profiler.countOperation("Best_Case_SelectionSort_comp", n, comp_selection);

	}
	profiler.addSeries("Best_Case_SelectionSort_sumOp", "Best_Case_SelectionSort_assign", "Best_Case_SelectionSort_comp");
}

void worst_case_selection(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		int* a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n);
		assign_selection = 0;
		comp_selection = 0;
		SelectionSort(a, n);

		

		profiler.countOperation("Worst_Case_SelectionSort_assign", n, assign_selection);
		profiler.countOperation("Worst_Case_SelectionSort_comp", n, comp_selection);

	}
	profiler.addSeries("Worst_Case_SelectionSort_sumOp", "Worst_Case_SelectionSort_assign", "Worst_Case_SelectionSort_comp");
}


void average_case_selection(int i, int max)
{
	int n;
	for (n = i; n <= max; n += i)
	{
		assign_selection = 0;
		comp_selection = 0;
		for (int i = 0; i < 5; i++)
		{
			int* a = (int*)malloc(n * sizeof(int));
			FillRandomArray(a, n);
			SelectionSort(a, n);
		}
		assign_selection /= 5;
		comp_selection /= 5;


		profiler.countOperation("Average_Case_SelectionSort_assign", n,assign_selection);
		profiler.countOperation("Average_Case_SelectionSort_comp", n, comp_selection);

	}
	profiler.addSeries("Average_Case_SelectionSort_sumOp", "Average_Case_SelectionSort_assign", "Average_Case_SelectionSort_comp");
}


// DEMO 
void insertion_sort_demo(int arr[], int n)
{

	int i, j, buff;
	for (i = 1; i < n; i++)
	{
		printf("\n  %d   ->   ", i);
		printArray(arr, n);

		buff = arr[i];
		j = i - 1;
		while (arr[j] > buff && j >= 0)
		{

			arr[j + 1] = arr[j];

			j = j - 1;
		}

		arr[j + 1] = buff;

	}
	printArray(arr, n);
}



void selection_sort_demo(int arr[], int n)
{
	int i, j, min, buff;
	for (i = 0; i < n - 1; i++)
	{

		printf("\n %d   ->   ", i);
		printArray(arr, n);


		min = i;

		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min]) min = j;
		}

		buff = arr[i];
		arr[i] = arr[min];
		arr[min] = buff;

	}
	printArray(arr, n);
}

void bubble_sort_demo(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		printf("\n %d   ->   ", i);
		printArray(a, n);

		for (j = 0; j < n - 1; j++)
		{

			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	printArray(a, n);
}

int main()
{
	int a[size] = { 1,54,3,56,2,234,45,3,9,10 };
	int b[size], c[size];
	CopyArray(b, a, size);
	CopyArray(c, a, size);
	

	printf("\nDEMO INSERTION \n");
	printArray(a, size);
	insertion_sort_demo(a, size);


	

	printf("\nDEMO SELECTION \n");
	printArray(b, size);
	selection_sort_demo(b, size);


	printf("\nDEMO FOR BUBBLE SORT \n");
	printArray(c, size);
	bubble_sort_demo(c, size);

// INSERTION SORT
		// best_case
	best_case_insertion(I, MAX);
	profiler.createGroup("Best_Case_Insertion", "Best_Case_InsertionSort_sumOp", "Best_Case_InsertionSort_assign", "Best_Case_InsertionSort_comp");

	// worst case
	worst_case_insertion(I, MAX);
	profiler.createGroup("Worst_Case_Insertion", "Worst_Case_InsertionSort_sumOp", "Worst_Case_InsertionSort_assign", "Worst_Case_InsertionSort_comp");

	// average case
	average_case_insertion(I, MAX);
	profiler.createGroup("Average_Case_Insertion", "Average_Case_InsertionSort_sumOp", "Average_Case_InsertionSort_assign","Average_Case_InsertionSort_comp");


// BUBBLE SORT 
// best case
	best_case_bubble(I, MAX);
	profiler.createGroup("Best_Case_Bubble", "Best_Case_BubbleSort_sumOp", "Best_Case_BubbleSort_assign", "Best_Case_BubbleSort_comp");

// average case
	average_case_bubble(I, MAX);
	profiler.createGroup("Average_Case_Bubble", "Average_Case_BubbleSort_sumOp", "Average_Case_BubbleSort_assign", "Average_Case_BubbleSort_comp");

	// worst case
	worst_case_bubble(I, MAX);
	profiler.createGroup("Worst_Case_Bubble", "Worst_Case_BubbleSort_sumOp", "Worst_Case_BubbleSort_assign", "Worst_Case_BubbleSort_comp");

		
// SELECTION SORT 

	//best case
	best_case_selection(I, MAX);
	profiler.createGroup("Best_Case_Selection", "Best_Case_SelectionSort_sumOp", "Best_Case_SelectionSort_assign", "Best_Case_SelectionSort_comp");

// average case
	average_case_selection(I, MAX);
	profiler.createGroup("Average_Case_Selection", "Average_Case_SelectionSort_sumOp", "Average_Case_SelectionSort_assign", "Average_Case_SelectionSort_comp");

	// worst case
	worst_case_selection(I, MAX);
	profiler.createGroup("Worst_Case_Selection", "Worst_Case_SelectionSort_sumOp", "Worst_Case_SelectionSort_assign", "Worst_Case_SelectionSort_comp");

		

	// All 3 methods graphs
	// Here we compare the number of total operations done by the algorithm
	profiler.createGroup("BEST sumOp", "Best_Case_InsertionSort_sumOp", "Best_Case_BubbleSort_sumOp", "Best_Case_SelectionSort_sumOp");
	profiler.createGroup("WORST sumOp", "Worst_Case_InsertionSort_sumOp", "Worst_Case_BubbleSort_sumOp", "Worst_Case_SelectionSort_sumOp");
	profiler.createGroup("AVERAGE sumOp", "Average_Case_InsertionSort_sumOp", "Average_Case_BubbleSort_sumOp", "Average_Case_SelectionSort_sumOp");

	// Here we compare the number of comparisons done by the algorithm in
	profiler.createGroup("BEST comp", "Best_Case_InsertionSort_comp", "Best_Case_BubbleSort_comp", "Best_Case_SelectionSort_comp");
	profiler.createGroup("WORST comp", "Worst_Case_InsertionSort_comp", "Worst_Case_BubbleSort_comp", "Worst_Case_SelectionSort_comp");
	profiler.createGroup("AVERAGE comp", "Average_Case_InsertionSort_comp", "Average_Case_BubbleSort_comp", "Average_Case_SelectionSort_comp");

	// Here we compare the number of asignments done by the algorithm
	profiler.createGroup("BEST assign", "Best_Case_InsertionSort_assign", "Best_Case_BubbleSort_assign", "Best_Case_SelectionSort_assign");
	profiler.createGroup("WORST assign", "Worst_Case_InsertionSort_assign", "Worst_Case_BubbleSort_assign", "Worst_Case_SelectionSort_assign");
	profiler.createGroup("AVERAGE assign", "Average_Case_InsertionSort_assign", "Average_Case_BubbleSort_assign", "Average_Case_SelectionSort_assign");


	profiler.showReport();

	_getch();
	return 0;
}