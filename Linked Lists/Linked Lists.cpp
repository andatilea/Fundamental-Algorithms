//Approach:

//- having k sorted lists and total of n values;
//- the lists are sorted in strictly ascending order;
//- the output result will also be stored in ascending order;
// For a small number of lists (2 in our case), the algorithm merges them and displays an ordered list;
//For k lists, the implementation contains a min-heap. It gets the minimum and puts it in the output, building the output list;

//How it works:
//- the min-heap is build from the first element of the k lists(in ascending order);
//- from each step, the top of the heap is put in the output and a new node(from the list) is added to the heap;
//- if a list is completely empty(we already taken all the elements), we reduce the heap size;
//- when we have only 2 lists, we merge them in sorted order, using SLL structure;

//Alternatives: instead of heap we could use a priority queque or Divide and Conquer;

//GRAPHS
//- for the first graph, we have a fixed number of lists(5, 10, 100) and we vary n from 100 to 10000
//- the number of operations increases if the number of lists grows;
//- this happens BECAUSE of the HEAP; a bigger heap requires more operations to be done;

//for the second graph, we have a fixed value n(=10000) and we vary the number of lists(k) from 10 to 500 using increments of 10;
//- the curve should have a running time of n*logk;

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

using namespace std;
Profiler profiler("Linked Lists");

#define SIZE 50000

int list_total_Op;

struct Node
{
	//data structure to store a linked list node
	int data;		//data of the node;
	struct Node* next;	//address of the next node;
};


struct SLL
{
	struct Node* first;
	struct Node* last;
	int nrElem;
};

int Emptylist(struct SLL l)
{
	list_total_Op++;			//1 comparison
	if (l.first == NULL)
		return 1;
	else return 0;
}

void initialize_list(struct SLL* l)
{

	l->first = NULL;
	l->last = NULL;
	l->nrElem = 0;

}

//insert a new node;
//the function is used as push;
//we have a SLL structure designed separately for the list and an int;
void push(struct SLL* l, int new_data)
{
	//firstly, allocate the node (create a node);
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	//put in the data
	new_node->data = new_data;

	//this node is going to be the last node, so make the next one NULL (a NULL is assigned);
	new_node->next = NULL;

	//if the list is empty then make the new node as head
	if (Emptylist(*l))
	{
		l->first = new_node;
		l->last = new_node;
	}

	//else transverse till the last node

	else
	{
		l->last->next = new_node;
		l->last = new_node; //point the previous last node to the new node created;
	}

	l->nrElem++;
}

//function to remove the first node of the linked list
void pop(struct SLL* l)
{
	if (Emptylist(*l) == 0)			// negative logic, if the list isn't empty;
	{
		Node* head = l->first;
		l->first = l->first->next;	//change head;
		l->nrElem--;
		free(head);				// free memory (free old head);
		list_total_Op += 2;
	}
}

//utility function to print linked list;
void displayList(struct SLL l)
{
	struct Node* node = l.first;
	if (Emptylist(l))
		printf("No list to display: list is empty");
	else

		while (node != NULL)
		{
			printf("%d ", node->data);
			node = node->next;
		}
	printf("\n");
}

void display_array(struct SLL l[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("\nThe List is: ");
		displayList(l[i]);
		printf("\n");
	}
}

//generate sorted array and put it in the list;
void build_List(struct SLL* l, int size)
{
	int arr[SIZE];
	FillRandomArray(arr, size, 1, 5 * size, true, 1);

	initialize_list(l);
	int i;
	for (i = 0; i < size; i++)
	{
		push(l, arr[i]);
	}
}


//	n= total number of elements
//  k= total number of lists
//  if we calculate we would have n/k elements in every list obtained;

void build_Lists(struct SLL list[], int n, int k)
{
	int i;
	int result = n / k;
	int aux = n % k;

	for (i = 0; i < k; i++)
	{
		if (aux > 0)
		{
			build_List(&list[i], result + 1);
			aux--;
		}

		else
		{
			build_List(&list[i], result);
		}
	}
}

//HEAPSORT

//min-Heap

void heapify(struct SLL l[], int n, int i)
{
	// the smallest item is the root;
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	list_total_Op++;			//comp
	//if left child is smaller;
	if (left < n && l[smallest].first->data > l[left].first->data)
	{
		smallest = left;
	}

	list_total_Op++;		//comp
	//if right child is smaller;
	if (right < n && l[smallest].first->data > l[right].first->data)
	{
		smallest = right;
	}

	// if smallest term is not the root;
	if (smallest != i)
	{
		//if one of the children is smaller we need to swap to get the smallest at the top;
		struct SLL aux = l[i];
		l[i] = l[smallest];
		l[smallest] = aux;

		list_total_Op += 3;			//swap->asign

		heapify(l, n, smallest);

	}

}
// algorithm to build a heap
void build_heap(struct SLL l[], int n)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		heapify(l, n, i);
	}
}

void print_heap(struct SLL l[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", l[i].first->data);
	}
	printf("\n");
}


//MERGE LISTS

//MergeSort is preferred for sorting linked lists;
void merging_2_lists(struct SLL l1, struct SLL l2, struct SLL* lo)
{
	//let first be the first node of the linked list to be sorted;
	Node* nl1 = l1.first;
	Node* nl2 = l2.first;

	//the head node has to be changed if the data is not the smallest value in the list;

	while (nl1 != NULL && nl2 != NULL)
	{
		// start with the linked list whose first data is the least;
		if (nl1->data < nl2->data)
		{
			push(lo, nl1->data);		//the element is placed in the output list;
			nl1 = nl1->next;
		}

		else
		{
			if (nl1->data > nl2->data)		//exactly the same but for l2;
			{
				push(lo, nl2->data);
				nl2 = nl2->next;
			}

			else
			{
				push(lo, nl1->data);
				push(lo, nl2->data);
				nl1 = nl1->next;
				nl2 = nl2->next;
			}
		}
	}

	while (nl1 != NULL)
	{
		push(lo, nl1->data);
		nl1 = nl1->next;
	}

	while (nl2 != NULL)
	{
		push(lo, nl2->data);
		nl2 = nl2->next;
	}
}

void merging_k_list(struct SLL l[], int k, struct SLL* lo)
{
	initialize_list(lo);

	int size = k;

	build_heap(l, k);

	//this function is created for more than 2 lists(merging 2 list is a separate function)
	while (size > 2)
	{
		push(lo, l[0].first->data);		//the first element is on the top of the heap;
		pop(&l[0]);

		if (Emptylist(l[0]) == 1)
		{
			l[0] = l[size - 1];

			size--;
		}

		heapify(l, size, 0);
	}
	//now we only have 2 lists because the rest of them contain 0 elements, we use the other function created;
	merging_2_lists(l[0], l[1], lo);
}

//GRAPH

//- for the first graph, we have a fixed number of lists(5, 10, 100) and we vary n from 100 to 10000
//- the number of operations increases if the number of lists grows;
//- this happens BECAUSE of the HEAP; a bigger heap requires more operations to be done;

void choose_n_variant(struct SLL l[], struct SLL* lo, int k)
{
	int n;
	char a[100];

	//we use sprintf because instead of printing on console it stores it on a char buffer;

	sprintf(a, "Total_Op_k=%d", k);

	initialize_list(lo);

	list_total_Op = 0;

	for (n = 100; n <= 10000; n = n + 100)
	{
		build_Lists(l, n, k);
		merging_k_list(l, k, lo);

		profiler.countOperation(a, n, list_total_Op);
	}
}

//for the second graph, we have a fixed value n(=10000) and we vary the number of lists(k) from 10 to 500 using increments of 10;
//- the curve should have a running time of n*logk;

void choose_k_variant(struct SLL l[], struct SLL* lo, int n)
{
	int k;
	char a[100];

	sprintf(a, "TotalOp_n=%d", n);

	initialize_list(lo);

	list_total_Op = 0;

	for (k = 10; k <= 500; k = k + 10)
	{
		build_Lists(l, n, k);
		merging_k_list(l, k, lo);

		profiler.countOperation(a, k, list_total_Op);
	}
}

//DEMO 
//MERGE 2 LISTS
void merging_2_lists_demo(struct SLL l1, struct SLL l2, struct SLL* lo)
{
	printf("\nDisplay the 2 lists to be merged: ");

	printf("\n1: ");
	displayList(l1);

	printf("2: ");
	displayList(l2);
	printf("\n");

	Node* nl1 = l1.first;
	Node* nl2 = l2.first;

	while (nl1 != NULL && nl2 != NULL)
	{
		// start with the linked list whose first data is the least;
		if (nl1->data < nl2->data)
		{
			push(lo, nl1->data);

			printf("Display result: \n");
			displayList(*lo);

			nl1 = nl1->next;
		}
		else
		{
			if (nl1->data > nl2->data)
			{
				push(lo, nl2->data);
				printf("Display result: \n");
				displayList(*lo);

				nl2 = nl2->next;
			}

			else
			{
				push(lo, nl1->data);
				printf("Display result: \n");
				displayList(*lo);

				push(lo, nl2->data);
				printf("Display result: \n");
				displayList(*lo);

				nl1 = nl1->next;
				nl2 = nl2->next;
			}
		}
	}

	while (nl1 != NULL)
	{
		push(lo, nl1->data);
		printf("Display result: \n");
		displayList(*lo);
		nl1 = nl1->next;
	}

	while (nl2 != NULL)
	{
		push(lo, nl2->data);
		printf("Display result: \n");
		displayList(*lo);
		nl2 = nl2->next;
	}
}

void merging_k_list_demo(struct SLL l[], int k, struct SLL* lo)
{
	initialize_list(lo);

	int size = k;
	build_heap(l, k);

	//this function is created for more than 2 lists(merging 2 list is a separate function)
	while (size > 2)
	{
		push(lo, l[0].first->data);
		printf("Display result: ");
		displayList(*lo);

		pop(&l[0]);

		if (Emptylist(l[0]) == 1)
		{
			l[0] = l[size - 1];

			size--;
		}

		heapify(l, size, 0);
	}
	//now we only have 2 lists because the rest of them contain 0 elements, we use the other function created;
	merging_2_lists(l[0], l[1], lo);

}

int main()
{
	int n = 20, k = 4;
	SLL l[SIZE];

	printf("\n*********************** Linked Lists start ******************************\n");
	build_Lists(l, n, k);
	display_array(l, k);
	printf("*********************** Linked Lists end ******************************\n");

	SLL lo;
	printf("\n*********************** Merge two Lists start ****************************\n");
	initialize_list(&lo);

	merging_2_lists_demo(l[0], l[1], &lo);
	printf("\nOutput: \n");
	displayList(lo);
	printf("\n*********************** Merge two Lists end ****************************\n");

	SLL lo2;
	printf("\n*********************** Merge k Lists start ****************************\n");
	merging_k_list_demo(l, k, &lo2);
	printf("\nOutput: \n");
	displayList(lo2);
	printf("\n*********************** Merge k Lists end ****************************\n");

	SLL lO;
	initialize_list(l);
	choose_n_variant(l, &lO, 5);
	choose_n_variant(l, &lO, 10);
	choose_n_variant(l, &lO, 100);

	profiler.createGroup("TotalOp_for_3_values_of_k", "Total_Op_k_5", "Total_Op_k_10", "Total_Op_k_100");

	choose_k_variant(l, &lO, 10000);

	//profiler.showReport();

	return 0;

}