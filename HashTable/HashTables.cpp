//the expected time for hash - table operations is O(1), so:
//WST case -> O(n);
//AVG case -> O(1);
//The HASH-INSERT procedure takes as input a hash table Tand a key k. It either returns the slot number where it stores key k or flags an error because the hash table is already full;
//The algorithm for searching for key k probes the same sequence of slots that the insertion algorithm examined when key k was inserted;

//The procedure HASH-SEARCH takes as input a hash table Tand a key k, returning j if it finds that slot j contains key k, or NIL if key k is not present in table T;

//We use the method of Quadratic probing. This method works much better than linear probing, but to make full use of the hash table, the values of c1, c2, and m are constrained.

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#include "Profiler.h"

#define N 10007
#define RANGE 100000
//positive auxiliary constants;
//for a hash table the values of c1, c2 will remain constant;
//for prime sizes (>2) we will choose c1 and c2 to be c1=c2=1;
//there are only ~ N/2 distinct probes for a given element, so it is difficult to guarantee that insertions will succeed when the load factor is >1/2;

#define c1 1
#define c2 1

int T[N];		////the variable T -> represents the Hash Table;
int arr[3001];

int countOp = 0;
int effortMax;
double effortAverage;
int notFound = 0;
int found = 0;

//hash function for linear probing
int HashLinear(int key)			//prime elements
{
	//where N is the size of the table;
	//in order to construct a linear probing we must have the second constant (c2) equal to 0;

	return key % N;
}
//hash function for quadric probing;
// the quadric probing uses a function of the form;
int HashQuadric(int key, int i)
{
	//where N is the size of the table;
	//if c2 would be 0 then the function will degrade to a linear probe;

	return(HashLinear(key) + c1 * i + c2 * i * i) % N;
}

//function to insert in the hash table;
//it succesively examine the Hash Table until an empty location is found;
int Hash_Insert(int k)
{
	//the variable k represents the key;
	int i, j;
	i = 0;

	do {
		j = HashQuadric(k, i);// get the index where the key will be inserted by calling the Hash function;

		if (T[j] == 0)	// if the spot is empty
		{
			T[j] = k;		//place the key;
			return j;		// return the index where the key has been inserted;
		}
		else
			i++;			//else move to the next location;
	} while (i != N);
	//if the index i is equal to N (the table size) then the table is filled up;
	return -1;
}

int Hash_Search(int k, int* accesses)
{
	int i, j;
	i = 0;
	do {
		(*accesses) = i + 1;
		//the variable represented by j is used as the position;
		j = HashQuadric(k, i);//computes the index;
		if (T[j] == k)				//if the value at the location is equal to the key
		{
			return j;		//returns the index at which the key has been found;
		}
		i++;				// else it keeps searching;
	} while (i != N && T[j] != 0);
	countOp++;
	return -1;
}

//function to print the array 
void print(int a[], int size) {				//Take an array a and define its values
	printf("\n");
	for (int i = 0; i < size; i++) {		//Loop for each value of a;
		if (a[i] != 0)
			printf("%d: %d \n", i, a[i]);		//Display a[i] where i is the value of current iteration
	}
}


//DEMOS
int insert_hash_demo(int T[], int k)
{
	int i = 0;
	while (i < N)
	{
		int j = HashQuadric(k, i);
		if (T[j] == 0)
		{
			T[j] = k;
			return j;
		}
		else
			i++;
	}
}

int search_hash_demo(int T[], int k)
{
	int i = 0;
	int j = HashQuadric(k, i);
	while (T[j] != 0 && i < N)
	{
		if (T[j] == k)
		{
			if (i > effortMax)
				effortMax = i;
			return j;
		}
		i++;
	}
	return 0;
}

//MAIN

int main()
{
	int search_Hash;
	insert_hash_demo(T, 1);
	insert_hash_demo(T, 12);
	insert_hash_demo(T, 15);
	insert_hash_demo(T, 19);

	printf("\n*************************************** TESTING THE 2 FUNCTIONS ********************************************\n");
	print(T, N);
	search_Hash = search_hash_demo(T, 12);
	printf("Testing Hash_Search function: the searched value is = %d\n", search_Hash);

	search_Hash = search_hash_demo(T, 33);
	printf("\nTesting Hash_Search function: the searched value is = %d\n", search_Hash);


	printf("\n*************************************** TESTING ENDS ********************************************\n\n\n");

	printf("\n\n******************************************OUTPUT TABLE********************************************\n\n\n");
	int n;
	int nr;
	int search;
	int searchC = 0;
	int length = 0;
	int access;

	double f_factor;

	double effortAverageFound = 0;
	double effortAverageNotFound = 0;

	int effortMaxFound = 0;
	int effortMaxNotFound = 0;

	int nrFound;
	int nrNotFound;

	int accessFound;
	int accessNotFound;

	printf("Filling factor | Avg. Effort found | Max. Effort found | Avg. Effort not-found | Max. Effort not-found\n");
	for (int k = 0; k < 5; k++)
	{
		//choose the fill factor
		switch (k)
		{
		case 0:
			f_factor = 0.80;
			break;
		case 1:
			f_factor = 0.85;
			break;
		case 2:
			f_factor = 0.90;
			break;
		case 3:
			f_factor = 0.95;
			break;
		case 4:
			f_factor = 0.99;
			break;
		}
		n = N * f_factor;

		//clean the arrays
		for (int i = 0; i < N; i++)
		{
			T[i] = 0;
		}

		for (int i = 0; i < 3000; i++)
		{
			arr[i] = 0;
		}
		length = 0;
		searchC = 0;
		effortAverageFound = 0;
		effortAverageNotFound = 0;

		effortMaxFound = 0;
		effortMaxNotFound = 0;

		nrFound = 0;
		nrNotFound = 0;

		accessFound = 0;
		accessNotFound = 0;

		//add random elements in the 2 arrays
		for (int i = 0; i < n; i++)
		{

			nr = rand() % RANGE + 1;			//keep random numbers under RANGE
			Hash_Insert(nr);

			if (i % 7 == 0)
			{
				arr[length++] = nr;
			}
		}


		for (int i = length; i < 3000; i++)
		{
			nr = rand() % RANGE + 1 + RANGE; //to be bigger
			arr[i] = nr;

		}
		for (int i = 0; i < 3000; i++)
		{
			access = 0;
			search = Hash_Search(arr[i], &access);
			searchC += access;

			if (search != -1)
			{
				accessFound += access;
				nrFound++;

				if (access > effortMaxFound)
					effortMaxFound = access;
			}
			else
			{
				accessNotFound += access;
				nrNotFound++;

				if (access > effortMaxNotFound)
					effortMaxNotFound = access;
			}
		}
		effortAverageFound = (double)accessFound / 3000;
		effortAverageNotFound = (double)accessNotFound / 3000;

		printf("      %.2f                   %f                   %d                   %f               %d\n", f_factor, effortAverageFound, effortMaxFound, effortAverageNotFound, effortMaxNotFound);
		_getch();
	}
	printf("\n\n******************************************OUTPUT TABLE ENDS*******************************************\n\n\n");
	_getch();
	return 0;
}



