/*
BFS:
Strategy:
-the algorithm explores the edges of the graph to discover every vertex that is reachable from s;
-it computes the distance= smallest number of edges from the source to each reachable vertex
-it also produces a 'breadth-first tree' with the root s(source) and all the reachable vertices;
-to keep track of the process we paint the vertices with white, gray or black;
- the tree created contains initially only its root (source vertex). Whenever the search discoveres a white vertex v, this vertex and the edge are added to the tree;
- to find the vertex v we are searching in the adjacency list of an already discovered vertex u;
-for simplicity, it is assumed that all vertices are reachable from the starting vertex;

TIME COMPLEXITY:
-the running time for BFS: O(V+E);


*/

#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

#include "Profiler.h"

using namespace std;

Profiler profiler("BFS");
#define max_vertices 500


typedef struct node {	//the structure of a vertex 
	int key, distance;
	int color;
	//white, not visited yet =0;
	//gray, in the stack=1;
	//black, out of the stack=2;
	struct node* parent;
}graph_node;

graph_node* vertices[max_vertices];		//the maximum for the assignment

typedef struct q_node {		//the node of the list;
	graph_node* v;
	struct q_node* next;	//pointer to the next node;
}queue_node;

typedef struct Queue {		//the list
	queue_node* first, * last;	//pointer to head node of the list and pointer to the last node of the list;
}queue;


// QUEUE
//insert an element(the node named: node) to the end of the queue (q)
//push function: insert at end
void en_queue(queue* q, graph_node* v)
{
	//a new queue element
	queue_node* aux = new queue_node();
	aux->v = v;
	aux->next = NULL;
	if (q->first == NULL)
	{
		//the second pointer created will become the first element;
		q->first = aux;
		q->last = aux;
	}
	else
	{
		//else we put it to the tail(end)
		q->last->next = aux;
		q->last = aux;
	}
}

//delete the first element from the queue
//pop function: delete at front
graph_node* de_queue(queue* q)
{
	queue_node* aux2 = q->first;	//create a new pointer;
	//the new pointer points to the first element of the list;
	if (aux2 != NULL)	//if list is not empty
	{
		q->first = q->first->next;	//the first element will become the element with the number 2(the next one)
		return aux2->v;
	}

	return NULL;
}

queue* adjacency_list[max_vertices];		//for each node we have an adjacency list;


bool edge_already_exists(queue* q, int v)
{
	queue_node* aux3 = q->first;	//create a new pointer; it points to the first element;
	while (aux3 != NULL)	//while it isn't empty
	{
		if (aux3->v->key == v)	//if it cpintains a known value
			return true;		//then we return true, the edge already exists;
		aux3 = aux3->next;		//and we move on to the next one;
	}
	return false;				//otherwise, we return false and the edge in cause doesn't exist
}

void create_vertices(int size)
{

	for (int i = 1; i <= size; i++)
	{
		vertices[i] = new graph_node();
		vertices[i]->key = i;
	}

}
//TRANSFORMATIONS

//MULTIWAY TREE
//declare what a node in this representation(MultiWay) contains:
typedef struct Node2 {
	//it contains a root and goes down from that;
	int key;		//the value from the node;
	int nrChildren;	 //number of succesors;
	struct Node2* children[20];	//we suppose the maximum number for the children is 20;
}Node2;

//we declare how a node looks in this representation(structure for BinaryTree);
//it cointains 2 pointers: one to the son, one to the right sibling;
typedef struct Node3 {
	int key;
	struct Node3* child, * sibling;	//we declare the first child; then we declare its sibling (it is always one);
}Node3;

//the root for the first representation
int* root1;
//array of multiway subtrees
Node2* nodes2[20];

//we proceed the first transformation from the parent array to the MultiWay representation
Node2* T1(int size)
{
	//size represents the number of elements;
	int i, nr;
	//declare the root and initialize it;
	Node2* root2 = NULL;
	//initialize all the nodes from this representation
	for (i = 1; i <= size; i++)
	{
		//allocate memory for the children;
		nodes2[i] = (Node2*)malloc(sizeof(Node2));
		nodes2[i]->key = i;
		nodes2[i]->nrChildren = 0;
		//find the root of the new representation, look for -1 in the array
		//-1 will always be the value of the root node index;
		if (root1[i] == -1)
			root2 = nodes2[i];
	}
	for (i = 1; i <= size; i++)
	{
		//if it is not the root then it becomes node
		if (root1[i] != -1)
		{
			nr = nodes2[root1[i]]->nrChildren;
			nodes2[root1[i]]->children[nr] = nodes2[i];
			nodes2[root1[i]]->nrChildren++;
		}
	}

	//returns the second representation
	return root2;
}

//we proceed the transformation from the MultiWay representation to the BinaryTree representation
Node3* T2(Node2* root) // root represent the current node
{
	//take the given parameter from MultiWay and make a node for the BinaryTree representation;
	//the root from the MultiWay representation will be the same with the root for BinaryTree representation;
	Node3* root3 = new Node3;
	root3->key = root->key; //setting the key
	//we check if the root has children;
	if (root->nrChildren == 0)
	{
		//if not, the child will be equal to NULL;
		root3->child = NULL;
	}
	else
	{
		int i;
		Node3* new_node2 = new Node3;
		//set the children
		//the first child from the BinaryTree representation will also be the first child from the MultiWay representation;
		//go recursively 
		new_node2 = T2(root->children[0]);
		//the first element will always be a child and the other ones will be siblings 
		new_node2->sibling = NULL;			//we initialize the brother;
		root3->child = new_node2;
		for (i = 1; i < root->nrChildren; i++)
		{
			//now we set the brother;
			new_node2->sibling = T2(root->children[i]);		//go recursively
			new_node2 = new_node2->sibling;
			new_node2->sibling = NULL;
		}
	}
	//return the value of the third representation;
	return root3;
}
//print function
void prettyPrint(Node3* root, int level)
{
	int i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
	if (root != NULL)
	{
		printf(" %d \n", root->key);
		if (root->child != NULL)
		{
			prettyPrint(root->child, level + 1);
		}
		if ((root->sibling) != NULL)
		{
			prettyPrint(root->sibling, level);
		}
	}
}

//BFS

//the BFS algorithm assumes that the input graph is represented using adjacency lists;
//it attaches several additional attributes to each vertex in the graph;
void BFS(int s, int V, int E)
{
	//s- represents the source node(also named the start node);
	//with the exception of the source vector, we paint every white vertex;
	for (int i = 1; i <= V; i++)
	{
		//we store the color of each vertex in the attribute u->color
		vertices[i]->color = 0;	//white
		vertices[i]->distance = INT_MAX;		//we set the distance to be almost infinity for each vertex
		//if the predecessor is NULL, it means that the node has not been discovered, or it is equal to the source node
		vertices[i]->parent = NULL;
		profiler.countOperation("OPS", V + E, 3);
	}
	//we paint s gray since we consider it to be discovered as the prodecure begins
	vertices[s]->color = 1;	//gray
	// it holds the distance from the source(initialize it);
	vertices[s]->distance = 0;
	//we create a queue q
	queue* q = new queue();
	//then, we initialize it
	q->first = q->last = NULL;

	profiler.countOperation("OPS", V + E, 3);
	//we make the queue to only contain the vertex s, so the queue is non-empty
	en_queue(q, vertices[s]);
	//u represents the gray vertex which is the head of the queue;
	graph_node* u = de_queue(q);	// remove it from the queue
	graph_node* v;
	//we stay in the while loop as long as there remain discovered vertices without their adjacency lists fully examined
	while (u != NULL)	//the queue consist of the set of gray vertices
	{
		//with the for loop, we consider each vertex v in the adjacency list of u
		for (v = de_queue(adjacency_list[u->key]); v != NULL; v = de_queue(adjacency_list[u->key]))
		{
			profiler.countOperation("OPS", V + E, 2); 

			//if v is white -> hasn't been yet discovered
			if (v->color == 0)
			{
				//we discover it
				v->color = 1;
				v->distance = u->distance + 1;	//set its distance
				v->parent = u;	//record u as its parent
				en_queue(q, v);	//we place it in the tail of the queue

				profiler.countOperation("OPS", V + E, 4);

			}
		}
		//once we examined all the vertices on u's adjacency list we paint u black
		u->color = 2;
		printf("\n");
		for (int t = 0; t < u->distance; t++) {
			cout << '\t';
		}
		printf("%d", u->key);
		u = de_queue(q);
		profiler.countOperation("OPS", V + E, 2);

	}

}

void create_graph(int V, int E)
{
	//the number of vertices represent the size
	int i, src, dest;
	for (i = 1; i <= V; i++)
	{
		adjacency_list[i] = new queue();
		// initialize the adjacency lists
		adjacency_list[i]->first = adjacency_list[i]->last = NULL;
	}
	for (i = 1; i <= E; i++)
	{
		src = rand() % V + 1;
		dest = rand() % V + 1;
		//verifying if the edge already exists
		while (edge_already_exists(adjacency_list[src], dest))
		{
			src = rand() % V + 1;
			dest = rand() % V + 1;
		}
		en_queue(adjacency_list[src], vertices[dest]);
	}

}

void print_graph(int V)
{
	for (int i = 1; i <= V; i++)
	{
		printf("\nNode: %d \n", i);
		queue_node* v;
		v = adjacency_list[i]->first;
		while (v != NULL)
		{
			printf("%d ", v->v->key);
			v = v->next;
		}
		printf("\n");
	}
}

void free_val(int nr_V)
{

	for (int i = 0; i < nr_V; i++)
	{
		free(adjacency_list[i]);
		free(vertices[i]);
	}

}

void demo() 
{
	
	int demo[max_vertices];
	int i;

	//create vertices of the graph
	create_vertices(6);

	//create the adjacency lists
	for (i = 1; i <= 6; i++)
	{
		adjacency_list[i] = new queue();
		adjacency_list[i]->first = adjacency_list[i]->last = NULL;	//initialize  it
	}

	create_graph(6, 6);
	//add data to the graph
	en_queue(adjacency_list[1], vertices[2]);
	en_queue(adjacency_list[1], vertices[6]);
	en_queue(adjacency_list[2], vertices[4]);
	en_queue(adjacency_list[2], vertices[6]);
	en_queue(adjacency_list[3], vertices[4]);
	en_queue(adjacency_list[4], vertices[2]);
	en_queue(adjacency_list[4], vertices[3]);
	en_queue(adjacency_list[5], vertices[6]);
	en_queue(adjacency_list[6], vertices[1]);
	en_queue(adjacency_list[6], vertices[2]);
	en_queue(adjacency_list[6], vertices[5]);
	print_graph(6);
	printf("\n");


	//apply BFS
	printf("BFS:\n");
	BFS(1, 6, 6);
	printf("\n");


	Node2* mRoot;
	mRoot = T1(6);
	Node3* bRoot;
	bRoot = T2(mRoot);
	//bRoot->sibling = NULL;
	prettyPrint(bRoot, 0);
}

void V_function()
{
	int E, V, src;
	//first case V-constant
	for (V = 100, E = 1000; E <= 5000; E += 100)
	{
		create_vertices(V);
		create_graph(V, E);
		src = rand() % V + 1;
		BFS(src, V, E);

	}
	free_val(max_vertices);
	profiler.createGroup("Operatii_E_variant", "OPS");
	profiler.showReport();
}

void E_function()
{
	int E, V, src;
	//second case E-constant
	free_val(max_vertices);
	for(E=9000,V=100;V<=200;V+=10)
	{
		create_vertices(V);
		create_graph(V,E);
		src=rand()%V +1;
		BFS(src,V,E);

	}

	profiler.createGroup("Operatii_V_variant", "OPS");
	profiler.showReport();
}


int main()
{
	int E, V, src;

	demo();
	_getch();

	//first case
	//V_function();

	//second case
	//E_function();
	
	
	return 0;
}