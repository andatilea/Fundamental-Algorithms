//we need 2 transformations - from R1->R2 and from R2->R3
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//the parent array
int arr[11]= { 0, 2, 7, 5, 2, 7, 7, -1, 5,2 };

//R2
//if create the first transformation, we arrive in R2 representation
//declare what a node in this representation(MultiWay) contains:
 typedef struct Node2 {
	 //it contains a root and goes down from that;
	int key;	//the value from the node;
	int nrChildren; //number of succesors;
   struct Node2* children[10];	//we suppose the maximum number for the children is 10;
}Node2;


//R3
//if we create the second transformation, we arrive in the R3 representation;
//we declare how a node looks in this representation(structure for BinaryTree);
//it cointains 2 pointers: one to the son, one to the right sibling;
typedef struct Node3 {
	int key;
	struct Node3* child;	//we declare the first child;
	struct Node3* sibling;	//then we declare its sibling (it is always one);
}Node3;

//declare the root and initialize it;
Node2* root2 = NULL;
//declare the the nodes for R2 transformation
Node2* nodes2[11];

//TRANSFORM R2
//we proceed the first transformation from the parent array to the MultiWay representation
void T12(int* arr, int n)
{
	//n is the number of elements;
	//initialize all the nodes from this representation
	for (int i = 1; i <= n; i++)
	{
		//allocate memory for the children;
		nodes2[i] = (Node2*)malloc(sizeof(Node2));
		nodes2[i]->key = i;
		nodes2[i]->nrChildren = 0;

		//initialize each child with NULL
		for (int j = 0; j < 10; j++)
		{
			nodes2[i]->children[j] = NULL;
		}
	}

	for (int i = 1; i < n; i++)
	{
		//find the root of the new representation, look for -1 in the array
		//-1 will always be the value of the root node index;
		if (arr[i] == -1)
		{
			root2 = nodes2[i];		
		}

		else
		{
			//if it is not the root then it becomes node

			//a child of the node
			Node2* successor = nodes2[i];

			//find its parent
			Node2* parent = nodes2[arr[i]];

			//add the successor in the parent's list
			//the number of children increases;
			parent->children[parent->nrChildren++] = successor;
		}
	}
}

void pretty_print1(Node2* root, int level)
{
	if (root != NULL)
	{
		for (int i = 1; i <= level; i++)
			printf("    ");
			printf("%d\n", root->key);

			//create a loop for every child
			for (int i = 0; i < root->nrChildren; i++)
			{
				//display the subtree with the root in i;
				pretty_print1(root->children[i], level + 1);
			}
		}
	}

//TRANSFORM R3
Node3* allocate_children(int key)
{
	Node3* new_node = (Node3*)malloc(sizeof(Node3));
	new_node->key = key;
	new_node->child = NULL;
	new_node->sibling = NULL;
	return new_node;
}

//we proceed the transformation from the MultiWay representation to the BinaryTree representation
Node3* T23(Node2* root)
{
	if (root == NULL)
	{
		return NULL;
	}

	else
	{
		//take the given parameter from MultiWay and make a node for the BinaryTree representation;
		//the root from the MultiWay representation will be the same with the root for BinaryTree representation;
		Node3* new_node = allocate_children(root->key);

		//we save the number of children in which we have to go through
		int nrChildren = root->nrChildren;

		//the first child from the BinaryTree representation will also be the first child from the MultiWay representation;
		//go recursively 
		new_node->child = T23(root->children[0]);

		//create a list with all the children of the parameter;
		//the first element will always be a child and the other ones will be siblings 

		Node3* list_successors;		//all the successors of the node;
		
		//as i said, the first element will always be the child
		list_successors = new_node->child;


		int i = 1;
		//we start from 1 because we will use the variable for all the other successors, excepting the first one;
		//the child is already saved;

		while (i < nrChildren)
		{
			list_successors->sibling = T23(root->children[i]);

			//if at this moment we still have children, the list must go on
			if (list_successors != NULL)
				list_successors = list_successors->sibling;

			i++;
		}
		return new_node;
	}
}

void pretty_print2(Node3* root, int level)
{
	if (root != NULL)
	{
		// create a loop for every child
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%d\n", root->key);

		pretty_print2(root->child, level + 1);
		pretty_print2(root->sibling, level);
	}
}

int main()
{
	int i;
	printf("Parent Array\n");
	for (i = 0; i <10; i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");


	printf(" Transformation12: ARRAY to MULTIWAY \n");
	T12(arr, 10);
	pretty_print1(root2, 0);

	printf("\nTransformation23: MULTIWAY to BINARY\n");
	Node3* root3 = (Node3*)malloc(sizeof(Node3) + 1);
	root3 = T23(root2);
	pretty_print2(root3, 0);

	return 0;
}

