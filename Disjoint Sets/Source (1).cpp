
//MakeSet(x) - creates a new set whose only member is x(a set from 1 element, each element being in its own set)
//FindSet(x) - look for the representative of an element in its set(returns a pointer to that representative of the unique set containing x);
//Union(x,y) - the union of 2 dynamic sets x and y into a new set, smaller to greater (in case they are equal it goes from first to last)
//Method: to implement a disjoint set with union: we must keep track of the ranks
//		- try to keep the smaller depth tree under the root of the deeper tree;
//		- we use the term rank instead of the height;
//If we indeed work with a MST, then the number of created edges, will be (V-1), where V is the number of vertices in the given graph;
//Steps: 1. Sort all the edges, considering their weight;
//		 2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far; if not, include the edge; if yes, discard it;
//		 3. Repeat the previous step, until there are (V-1) edges in the spanning tree;
//TIME COMPLEXITY: 
//	- Alone, Union by Rank has a running time of O(mlgn)
//	- When we use both union by rank and path compresion, the worst case running time is O(m f(n)), where f(n) - very slowly growing function
//	- In applications, f(n)<4 so we can view the running time as linear in m (however, it is superlinear);
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler("Disjoint Sets");

int n;

//create a structure to represent a subset;
typedef struct Node {
	int key;		//value of the node;
	int rank;		//in addition, we keep track of the rank;
	struct Node* parent;		// the parent;
}Node;

//MakeSet- creates a tree with only one node;
//O(1) time complexity;
//MakeSet- in other words, create a set whose only element will be x (in our case, key);
Node* make_Set(int key)
{
	//with this function we also check the sub-function in which we set the Node Key;
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
		return NULL;
	else {
		new_node->key = key;
		new_node->rank = 0;	//it has the initial rank equal to 0;
		new_node->parent = new_node; //the element is the representative member of its own set;

		profiler.countOperation("Disjoint Sets: Operations", n, 1);
		return new_node;
	}
}

//FindSet- it makes each node on the find path to point directly to the root
//		 - the rank does not change;
//		 - the path compression is used;
//always return the root for the entire tree
Node* find_Set(Node* x)
{
	profiler.countOperation("Disjoint Sets: Operations", n, 1);
	if (x != x->parent)		// it makes one pass to find the root
	{

		x->parent = find_Set(x->parent);	//it makes the second pass to update each node, recursively find the representative;
	}
	return x->parent;	//return the pointer that points directly to the root;
}

//we use the link function to successfully link 2 sets, from the smaller to the larger;
//for each node we maintain a rank;
//in our case we have the node x, and the node y, it takes the pointers of 2 roots, as inputs;
// x->rank - is an integer which represents the number of edges in the longest simple path between x and a descendent (leaf);
void link_Set(Node* x, Node* y)
{
	profiler.countOperation("Disjoint Sets: Operations", n, 1);
	//attach a smaller rank tree under the root of the high rank tree;
	if (x->rank > y->rank)		//we must compare ranks;
	{
		profiler.countOperation("Disjoint Sets: Operations", n, 1);
		y->parent = x;			// make the root with higher rank the parent of the root with lower rank;
	}
	else
	{
		profiler.countOperation("Disjoint Sets: Operations", n, 2);
		x->parent = y;		// else we choose one of the roots to be the parent;

		if (x->rank == y->rank)		//if they have equal ranks;
			y->rank = y->rank++;	//increment the resulting set's rank by one;

	}
}
//this function realizes the union of 2 sets of x and y;
//we use Union by rank
void union_Set(Node* x, Node* y)
{
	link_Set(find_Set(x), find_Set(y));
}

void print_all(Node** nodes_array, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("Node %d is in set %d \n", nodes_array[i]->key, find_Set(nodes_array[i])->key);
	}
}

//we create a structure to represent a weighted edge in the graph;
typedef struct Edge {
	int weight;			//the value of the edge;
	struct Node* src;	//the source node: from where the edge starts;
	struct Node* dest;	// the destination node: where the edge arrives;
}Edge;


//we create a structure to represent a connected, undirected and weighted graph;
typedef struct Graph {
	int V;	//the number of Vertices
	int E;	//the number of Edges
//the graph is represented as an array of edges;
//since the graph is undirected, the edge from src to dest is also edge from dest to src (both are counted as 1 edge)
	struct Edge* edge;		//an array of edges;
}Graph;

//create a Graph with V vertices and E edges
Graph* create_Graph(int V, int E)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL)
		return NULL;
	else {
		graph->V = V;
		graph->E = E;
		graph->edge = (Edge*)malloc(E*sizeof(Edge));
		return graph;
	}
}

// partition function: takes the last element as pivot, places it at its correct position in the sorted array, place all the smaller values to the left, and all greater elements to the right of the pivot;
int partition(Edge array[], int l, int h) {
	int x = array[h].weight;		//declare the pivot;
	int i = l - 1;		//it takes the index of a smaller element;
	for (int j = l; j <= h - 1; j++)
	{
		if (array[j].weight <= x) {			//if the current element is smaller than the pivot;
			i++;			//increment the index of the smaller element;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[h]);
	return i + 1;
}

// quicksort - for sorting the array of edges
//array[]- the array to be sorted;
// l - starting index
// h - ending index;
void quicksort(Edge array[], int l, int h) {
	int q;	// q is a partitioning index;
	if (l < h) {
		//it means that array[q] is now at its right place;
		q = partition(array, l, h);
		//sort the elements before;
		quicksort(array, l, q - 1);
		//and separately, sort the element after the partition;
		quicksort(array, q + 1, h);
	}
}

//find the minimum spanning tree
Edge* min_Stree;	// the graph represented as an array od edges;
int j;


//the main function to construct a minimum Spanning Tree using Kruskal's algorithm
void Kruskal(Graph* new_graph)
{
	j = 0;

	int E = new_graph->E;
	int V = new_graph->V;

	//for each vertex of the graph we make a set with only one element
	for (int v = 1; v <= V; v++)
		make_Set(v);
	//we allocate the needed memory for the minimum spanning tree;
	min_Stree = (Edge*)malloc(E * sizeof(Edge));
	//realize the sorting;
	quicksort(new_graph->edge, 0, new_graph->E - 1);

	//go through the list of edges
	for (int i = 0; i < E; i++)
	{
		//the smallest one must be chosen
		Edge aux = new_graph->edge[i];

		Node* x = find_Set(aux.src);
		Node* y = find_Set(aux.dest);

		//we check: if we include this particular edge we will obtain a cycle
		if (x != y)
		{
			//if not, we add it to the minimum Spanning Tree;
			if (min_Stree != NULL)
			{
				min_Stree[j++] = aux;
				union_Set(x, y);
			}
		}
		//otherwise, we discard it;
	}
	//we repeat this until we have (V-1) edges in the spanning tree;
}

//demo function to test the Set Operations on a small input - 10 numbers
void DEMO_Sets()
{
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };

	Node** nodes_arr = (Node**)malloc(10 * sizeof(Node));

	printf("********************** DEMO *****************\n\n");
	printf(" Operations on Sets :\n");
	printf("\n             Before Operation:\n");

	for (int i = 0; i < 10; i++)
	{
		if (nodes_arr == NULL)
			return;
		else {
			nodes_arr[i] = make_Set(arr[i]);
			printf("%d -> %d\n", nodes_arr[i]->key, find_Set(nodes_arr[i])->key);
		}
	}

	printf("\n            After Operations:\n");
	//we will make 5 unions
	printf("\n First UNION: 0, 1: \n");
	union_Set(nodes_arr[0], nodes_arr[1]);
	print_all(nodes_arr, 10);
	printf("\nSecond UNION: 3, 7: \n");
	union_Set(nodes_arr[3], nodes_arr[7]);
	print_all(nodes_arr, 10);
	printf("\nThird UNION: 2, 6: \n");
	union_Set(nodes_arr[2], nodes_arr[6]);
	print_all(nodes_arr, 10);
	printf("\n4th UNION: 4, 8: \n");
	union_Set(nodes_arr[4], nodes_arr[8]);
	print_all(nodes_arr, 10);
	printf("\n5th UNION: 5, 6: \n");
	union_Set(nodes_arr[5], nodes_arr[6]);
	print_all(nodes_arr, 10);

	//we will make 5 find_set functions
	printf("\n First FIND: 5\n");
	Node* aux = find_Set(nodes_arr[5]);
	printf(" The Set that cointains %d is: %d\n", nodes_arr[5]->key, aux->key);
	//if we want to see all the other nodes meanwhile we are searching for one, we use the following function;
	//print_all(nodes_arr, 10);

	printf("\n Second FIND: 4\n");
	aux = find_Set(nodes_arr[4]);
	printf(" The Set that cointains %d is: %d\n", nodes_arr[4]->key, aux->key);
	//if we want to see all the other nodes meanwhile we are searching for one, we use the following function;
	//print_all(nodes_arr, 10);

	printf("\n Third FIND: 3\n");
	aux = find_Set(nodes_arr[3]);
	printf(" The Set that cointains %d is: %d\n", nodes_arr[3]->key, aux->key);
	//if we want to see all the other nodes meanwhile we are searching for one, we use the following function;
	//print_all(nodes_arr, 10);

	printf("\n 4th FIND: 2\n");
	aux = find_Set(nodes_arr[2]);
	printf(" The Set that cointains %d is: %d\n", nodes_arr[2]->key, aux->key);
	//if we want to see all the other nodes meanwhile we are searching for one, we use the following function;
	//print_all(nodes_arr, 10);

	printf("\n 5th FIND: 1\n");
	aux = find_Set(nodes_arr[1]);
	printf(" The Set that cointains %d is: %d\n", nodes_arr[1]->key, aux->key);
	//if we want to see all the other nodes meanwhile we are searching for one, we use the following function;
	//print_all(nodes_arr, 10);
}

//demo to test the Kruskal Algorithm with a small input; we choose a tree with a known number of vertices and edges;
void DEMO_KRUSKAL()
{
	printf("\n\n         Kruskal: DEMO\n");

	int V = 9;		//the number of vertices for the demo
	int E =14;		//edges

	//we build a graph with the given numbers
	Graph* graph = create_Graph(V, E);

	//build the array of vertices; 
	//for each one of the vertices we create a new set which contains only one element;
	Node** vertices = (Node**)malloc((V + 1) * sizeof(Node*));
	for (int v = 1; v <= V; v++)
	{
		if (vertices == NULL)
			return;
		else {
			vertices[v] = make_Set(v);
		}
	}

	//add the edges to the graph
	graph->edge[0].src = vertices[1];
	graph->edge[0].dest = vertices[2];
	graph->edge[0].weight = 10;

	graph->edge[1].src = vertices[1];
	graph->edge[1].dest = vertices[3];
	graph->edge[1].weight = 12;

	graph->edge[2].src = vertices[2];
	graph->edge[2].dest = vertices[3];
	graph->edge[2].weight = 9;

	graph->edge[3].src = vertices[2];
	graph->edge[3].dest = vertices[4];
	graph->edge[3].weight = 8;

	graph->edge[4].src = vertices[3];
	graph->edge[4].dest = vertices[4];
	graph->edge[4].weight = 3;

	graph->edge[5].src = vertices[3];
	graph->edge[5].dest = vertices[6];
	graph->edge[5].weight = 1;

	graph->edge[6].src = vertices[4];
	graph->edge[6].dest = vertices[5];
	graph->edge[6].weight = 7;

	graph->edge[7].src = vertices[4];
	graph->edge[7].dest = vertices[7];
	graph->edge[7].weight = 8;

	graph->edge[8].src = vertices[4];
	graph->edge[8].dest = vertices[8];
	graph->edge[8].weight = 5;

	graph->edge[9].src = vertices[5];
	graph->edge[9].dest = vertices[6];
	graph->edge[9].weight = 3;

	graph->edge[10].src = vertices[6];
	graph->edge[10].dest = vertices[8];
	graph->edge[10].weight = 6;

	graph->edge[11].src = vertices[7];
	graph->edge[11].dest = vertices[8];
	graph->edge[11].weight = 9;

	graph->edge[12].src = vertices[7];
	graph->edge[12].dest = vertices[9];
	graph->edge[12].weight = 2;

	graph->edge[13].src = vertices[8];
	graph->edge[13].dest = vertices[9];
	graph->edge[13].weight = 11;

	Kruskal(graph);

	//print the edges from the minimum SpanningTree
	//if the algorithm is correct, we will obtain (V-1) edges;
	for (int i = 0; i < j; i++)
	{
		printf("Src: %d Dest: %d , weight: %d \n", min_Stree[i].src->key, min_Stree[i].dest->key, min_Stree[i].weight);
	}
	printf("**************** DEMO ENDS********************\n");
}
//we include in the main function, the demo to build the graph of the total number of calls made to the disjoint set of operations;
//we look at it as a function of n - the total number of makeSet operations- average case analysis
//n varies between 100 and 10000;
int main()
{
	//FOR THE DEMO
	DEMO_Sets();

	DEMO_KRUSKAL();
	//END DEMO


	//GRAPH
	int edgesWeights[40001];
	int i;
	for (n = 100; n <= 10000; n += 100)
	{
		// make an array of vertices
		Node** vertices = (Node**)malloc((n + 1) * sizeof(Node*));
		// make an array of weights which will be set to the edges
		FillRandomArray(edgesWeights, 40000, 1, 50000, false, 0);
		//make the graph
		Graph* graph = create_Graph(n, n * 4);

		// make a set for each vertex containing only one element;
		for ( i = 1; i <= n; i++)
			vertices[i] = make_Set(i);

		// compute the edges of the graph
		for (i = 0; i < 4 * n; i++) {
			graph->edge[i].src = vertices[(rand() % n) + 1];
			graph->edge[i].dest = vertices[(rand() % n) + 1];
			graph->edge[i].weight = edgesWeights[i];
		}

		Kruskal(graph);
	}

	profiler.createGroup("Disjoint Sets: Operations", "OPERATIONS");
	profiler.showReport();

	return 0;
}
