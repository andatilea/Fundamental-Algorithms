//DFS Strategy: 
//- it searches 'deeper' in the graph whenever possible;
//-the search is realized for the edges of the most recently discovered vertex (v) that still has unexplored edges leaving it;
//-once all the v's edges have been explored, the search 'backtracks' to explore edges leaving the vertex from which v was discovered
//-we do this procedure until all the vertices are discovered;
//-if any undiscovered vertices remain, the DFS selects one of them as a new source and it repeats the search from that source;

//Simillarity with BFS:
//- whenever DFS discoveres a vertex v during a scan of the adj list of an already discovered vertex u, this u will become v's predecessor attribute;
//-searching colors vertices to indicate their state; Every vertex is initially white, then it is grayed when it is discovered in the search, and is blackened when it is finished(that is when its adj list has been examined completely)
//													- this procedure guarantees that each vertex ends up in exactly one tree, so the trees are disjoint;

//Differences between BFS & DFS:
//BFS: its predecessor subgraph forms a tree;
//DFS: - its predecessor subgraph may be composed of several trees, because the search may repeat from multiple sourcees;
//	 - each vertex contains 2 timestamps: discovery time(records when 'v' is first discovered, and grayed) and the second timestamp: finish time(records when the search finished examining v's adjacency list, and blackens v);
//	 - always dicovery time< finish time

//Time Complexity:
//	- the total cost of DFS-Visit is O(E);
//	- the running time of DFS is O(V+E);
//	- the running time of Topological Sort is O(V+E); 
//	- time complexity for Tarjan : WST Case: O(V+E);

//Topological Sort:
//	-represents a linear ordering of all its vertices (if the graph contains edge u-v then u must appear before v in the ordering);
//	-if the graph contains a cycle then no linear ordering is possible;
//	-we can see it as an ordering of its vertices along a horizontal line so that all directed edges go from left to right;
//	-it takes O(1) to insert each of the vertices onto the front of the list;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <list>
#include <stack>
#include "Profiler.h"

using namespace std;
Profiler profiler("DFS");

// number of vertices and edges
int V, E;

// discovery time
int t = 0;			//it represents a global variable that we use for timestamping

// topological sorting
bool visited = false;		//to mark the current node as visited (or not)

// types of colors for a node
enum Color {
	white, // not visited yet (every vertex is initially white)
	gray, // in the stack (when it is discovered in the search)
	black // out of the stack (finished,when its adjacency list has been examined completely)
};

// types for edges
enum Type {
	tree,		//represent the edges in the depth-first forest (edge u-v is a tree edge is v was first discovered by exploring the edge u-v)
	back,		//represent the edges which are connecting a vertex u to an ancestor v in a depth-first tree;
	forward,	//represent the non-tree edges which are connecting a vertex u to a descendant v in a depth-first tree;
	cross		//represent all the other edges (can go between vertices in the same tree, as long as one vertex is not an ancestor of the other; between vertices in different trees);
};

// node of the adjaceny list
typedef struct node_adj {
	int destination;
	Type type;	//the type of the edge
	struct node_adj* next;	
}node_adj;

// each node has an adjacency list(can call it a linkedList)
typedef struct list_adj {
	int discovery_time;		//when the node is first discovered, and grayed
	int finish_time;		// when the search finished examining the node's adjacency list, and blackens it;
	int parent;
	Color color;	//color of the node
	struct node_adj* head;	
}list_adj;

typedef struct graph	
{
	int V; //number of vertices;
	struct list_adj* adjacency_lists; // array of adjacency lists
}Graph;

//utility function that creates a graph of V vertices;
Graph* create_graph(int V)
{
	Graph* new_graph = (Graph*)malloc(sizeof(Graph));

	new_graph->V = V;	//the size of the array will be V;
	// a graph is an array of adjacency lists;
	// each vertex of the graph will have an adjacency_list;
	new_graph->adjacency_lists = (list_adj*)malloc(V * sizeof(list_adj));
	//we initialize each adjancency list as empty by making the head as NULL;
	for (int i = 0; i < V; i++) {
		new_graph->adjacency_lists[i].head = NULL;
	}
	return new_graph;
}
//utility function to create a new adjacency list node
node_adj* create_node(int destination)
{
	node_adj* new_node = (node_adj*)malloc(sizeof(node_adj));
	new_node->destination = destination;
	new_node->next = NULL;
	return new_node;
}

// add an edge to the graph
void add_edge_to_graph(Graph* graph, int src, int dest)
{
	// add an edge from src=source to dest=destination;
	node_adj* new_node2 = create_node(dest);
	// a new node is added to the adjacency list of src;
	new_node2->next = graph->adjacency_lists[src].head;
	// The node is added at the beginning;
	graph->adjacency_lists[src].head = new_node2;

}

typedef struct topological_node
{
	int key;
	struct topological_node* next;
}topologicalNode;


topological_node* new_topological_node = (topological_node*)malloc(sizeof(topological_node));


topological_node* create_topological_node(int key)
{
	topological_node* new_node3 = (topological_node*)malloc(sizeof(topological_node));
	new_node3->key = key;
	new_node3->next = NULL;
	return new_node3;
}

void add_topological_node(topological_node* head, int key)
{
	topological_node* new_node4 = create_topological_node(key);
	new_node4->next = head->next;
	head->next = new_node4;
}


void dfs_visit(Graph* graph, int u) 
{
	//u represent the root of a new tree in the depth_first forest;

	t++;	//the white vertex u just has been discovered -> increment global variable time;
	graph->adjacency_lists[u].discovery_time = t;	 //the new value of the time is recorded as the discovery time
	graph->adjacency_lists[u].color = gray;	//paint 'u' as gray

	profiler.countOperation("DFS", V + E, 2);	//assign

	printf(" %d", u);

	node_adj* v = graph->adjacency_lists[u].head;		//we must explore the edge (u,v) using the search

	//we will examine each vertex v, adjacent to u
	while (v != NULL) 
	{
		profiler.countOperation("DFS", V + E, 1);	//comp

		if (graph->adjacency_lists[v->destination].color == white)  //if it is white
		{
			v->type = tree; // is a tree edge because v was first discovered by exploring the edge u -v (being white before)
			graph->adjacency_lists[v->destination].parent = u;	//set the parent to be u
			dfs_visit(graph, v->destination); // recursively visit v 
		}
		else 
		{
			profiler.countOperation("DFS", V + E, 1);	//comp
			if (graph->adjacency_lists[v->destination].color == gray)  //it means v is already verified
			{
				visited = false;	//mark all the nodes as not visited
				v->type = back;	//so it is a back Edge because it is connecting the vertex u to an ancestor v-already checked
			}
		}
		v = v->next;
	}
	//after we explore every edge which is leaving u

	profiler.countOperation("DFS", V + E, 2);

	graph->adjacency_lists[u].color = black;	//we blacken u; so it is finished;

	if (visited == true)	//if the nodes are visited
		add_topological_node(new_topological_node, u);

	t++;	//increment the time
	graph->adjacency_lists[u].finish_time = t;	//record the finishing time
}

void DFS(Graph* graph, int s)		//the graph may be directed or undirected
{
	//here, s represents the source
	//create a loop for each vertex in the G.V graph
	for (int i = 0; i < graph->V; i++)
	{
		profiler.countOperation("DFS", V + E, 2);	//assign
		//always the vertex will be WHITE before the discovery time;
		//so, we paint all the vertices white;
		graph->adjacency_lists[i].color = white;
		//we initialize their predecessors to NIL;
		graph->adjacency_lists[i].parent = NULL;
	}
	t = 0;			//reset the global variable for timestamping (time counter)
	//create a loop for each vertex in the G.V graph
	for (int i = 0; i < graph->V; i++) 
	{

		profiler.countOperation("DFS", V + E, 1);	//comp

		if (graph->adjacency_lists[i].color == white)	//when a white vertex is found
			dfs_visit(graph, i);		//we visit it using dfs_visit function
		//every time we call this function, the vertex u will become the root of a new tree in the forest;
	}
}

void topological_sort(Graph* graph)
{
	visited = true;
	DFS(graph, 0);	//we call DFS to compute the finishing times for each vertex v
	topological_node* v = (topological_node*)malloc(sizeof(topological_node));
	//as each vertex is finished, we insert it onto the front of the list
	v = new_topological_node->next;			

	printf("\n\nTopological Sort:\n");
	if (visited == false) 
	{
		printf("Not possible \n");
	}
	else
	{
		while (v)
		{
			printf(" %d", v->key);	//return the list of vertices
			v = v->next;
		}
	}
}
//utility function to print the adjacency list representation of the graph
void print_graph(Graph* graph)
{
	for (int i = 0; i < graph->V; i++)
	{
		node_adj* new_node7 = graph->adjacency_lists[i].head;

		printf("Adjacency list of %d", i);
		while (new_node7)
		{
			printf("-> %d ", new_node7->destination);
			new_node7 = new_node7->next;
		}
		printf("\n");
	}
}

// TARJAN ALGORITHM 

//create a class that represents an directed graph
class graph_tarjan
{
	int V;		//declare the number of vertices
	list<int>* array_lists;	//create a dynamic array of adjacency lists

//declare a recursive DFS based function used by SCC()
void SCC_function(int u, int disc[], int low[], stack<int>* st, bool stackMember[]);

public:
	graph_tarjan(int V);		//the constructor
	void add_edge(int v, int w);		//create a function to add an edge to the graph
	void SCC();		//it strongly prints the connected components
};

graph_tarjan::graph_tarjan(int V)
{
	this->V = V;
	array_lists = new list<int>[V];
}

void graph_tarjan::add_edge(int v, int w)
{
	array_lists[v].push_back(w);
}

//now we must create a recursive function that finds and prints the strongly connected components using the DFS transversal
// u -> represents the vertex to be visited next
//disc[] -> stores the discovery times of the visited vertices
//low[] -> represents the earliest visited vertex (the vertex with the minimum discovery time) that can be reached from the subtree rooted at the current vertex
//*st -> we use it to store all the connected ancestors (could be a part of the SCC)
// stackMember[] -> it represents whether a node is in the stack

void graph_tarjan::SCC_function(int u, int disc[], int low[], stack<int>* st, bool stackMember[])
{
	// we declare a static variable
	static int time = 0;

	// initialize discovery time and low value
	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;

	// go through all adjacent vertices
	list<int>::iterator i;
	for (i = array_lists[u].begin(); i != array_lists[u].end(); ++i)
	{
		int v = *i;			// v is current adjacent of 'u'

		// if v is not visited yet, then go recursively for it
		if (disc[v] == -1)
		{
			SCC_function(v, disc, low, st, stackMember);

			// check if the subtree rooted with 'v' has a connection to one of the ancestors of 'u'
			// Case 1: tree edge 

			low[u] = min(low[u], low[v]);	//has not yet been visited;
		}

		// update low value of 'u' only if 'v' is still in stack
		// Case 2: back edge
		else if (stackMember[v] == true)		//v is in stack, hence in the SCC
			low[u] = min(low[u], disc[v]);
		//if v is not in stack, a cross edge will be created and that case is ignored;
	}

	// root node found, pop the stack and print an SCC
	int w = 0;				// to store stack extracted vertices
	if (low[u] == disc[u])		//start a new SCC
	{
		while (st->top() != u)
		{
			w = (int)st->top();
			printf("%d ", w);
			stackMember[w] = false;
			st->pop();
		}
		w = (int)st->top();
		//nodes are not popped (and printed) as the search returns up the tree; they are only popped when an entire SCC has been found;
		printf("%d\n", w);
		stackMember[w] = false;
		st->pop();
	}
}

// the function to do DFS traversal using SCC
void graph_tarjan::SCC()
{
	int* disc = new int[V];
	int* low = new int[V];
	bool* stackMember = new bool[V];
	stack<int>* st = new stack<int>();

	// initializations for the disc and low values, and also the stackMember arrays
	for (int i = 0; i < V; i++)
	{
		disc[i] = -1;
		low[i] = -1;
		stackMember[i] = false;
	}

	// Call SCC_f(the recursive helper function) to find the strongly connected components in DFS tree with the vertex 'i'(in other words, for every undiscovered node)
	for (int i = 0; i < V; i++)
		if (disc[i] == -1)
			SCC_function(i, disc, low, st, stackMember);
}

void demo()
{
	// DEMO
	V = 5;
	printf("**********************************DEMO***********************************\n");
	Graph* graph2 = create_graph(V);

	//add_edge_to_graph(graph2, 1, 0);
	//add_edge_to_graph(graph2, 0, 2);
	//add_edge_to_graph(graph2, 2, 1);
	//add_edge_to_graph(graph2, 0, 3);
	//add_edge_to_graph(graph2, 3, 4);

	add_edge_to_graph(graph2, 1, 0);
	add_edge_to_graph(graph2, 2, 1);
	add_edge_to_graph(graph2, 3, 4);
	add_edge_to_graph(graph2, 4, 0);
	

	printf("Adjacency lists:\n");
	print_graph(graph2);		//print the adjacency list representation of the above graph

	printf("\n");
	printf("DFS:\n");
	

	// in a toppological sort a vertex should be printed before its adjacency nodes
	// because of this, topological sort is different from DFS
	topological_sort(graph2);


	printf("\n\nTarjan Algorithm:\n");
	printf("SCCs in the graph:\n");

	graph_tarjan g1(7);
	g1.add_edge(0, 1);
	g1.add_edge(1, 2);
	g1.add_edge(2, 0);
	g1.add_edge(1, 3);
	g1.add_edge(1, 4);
	g1.add_edge(1, 6);
	g1.add_edge(3, 5);
	g1.add_edge(4, 5);
	g1.SCC();
}

void function_E()	//generate the variation of the number of operations with E
{
	// first case
	
	int source, destination;
	V = 100;
	for (E = 1000; E < 5000; E += 100) {
		Graph *graph = create_graph(V);
		for (int i = 1; i <= E; i++) {
			do {
				source = rand() % 100;		//where the edge begins
				destination = rand() % 100;	//where the edge ends
			} while (source == destination);
			add_edge_to_graph(graph, source, destination);
		}
		DFS(graph, 0);		//we run the DFS algorithm for each V, E pair;
	}

	profiler.createGroup("DFS_E_variant", "DFS");
	profiler.showReport();
	
}

void function_V()		//generate the varation of the number of operations with V
{
	// second case

	int source, destination;
	E = 9000;
	for (V = 100; V <= 200; V += 10) {
		Graph *graph = create_graph(V);
		for (int i = 1; i <= E; i++) {
			do {
				source = rand() % 100;
				destination = rand() % 100;
			} while (source == destination);
			add_edge_to_graph(graph, source, destination);
		}
		DFS(graph, 0);  //we run the DFS algorithm for each V, E pair;
	}

	profiler.createGroup("DFS_V_variant", "DFS");
	profiler.showReport();
	
}
int main() 
{
	//initialize the topological node
	new_topological_node->next = NULL;
	//DEMO
	demo();

	//first case
	//function_E();


	//second case
	//function_V();

	return 0;
}

