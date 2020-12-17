#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
//#include "queue.h"
#include "graph.h"

#define VERTICES 6

int capacities[VERTICES][VERTICES];

int flowPassed[VERTICES][VERTICES];

int parentsList[VERTICES];

int currentPathCapacity[VERTICES];



typedef struct graph2 {
    int v;
    int e;
    int **adj;
} Graph2;

void allocate_mem(int*** arr, int n, int m) {
    *arr = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        (*arr)[i] = (int*) malloc(m*sizeof(int));
    }
}

Graph2* adjMatrixOfGraph() {
    int u,v,i;

    Graph2 *G = malloc(10*6*sizeof(Graph2));
    allocate_mem(&G->adj, 10, 10);
    
    G->e = 10;
    G->v = 10;

    for (u = 0; u < G->v; u++) {
        for (v = 0; v < G->v; v++) {
            G->adj[u][v] = 0;
        }
    }

    for (int i = 0; i < G->v; i++) {
        for (int j = 0; j < G->v; j++) {
            printf("%2d ", G->adj[i][j]);
        }
        printf("\n");
    }

    printf("Adj: %d\n", G->adj[1][0]);
}



typedef struct stack {
    int top;
    int sizeOfstack;
    int *array;
} Stack;

Stack* createStack(int sizeOfstack) {
    Stack *stack = (Stack* )malloc(sizeof(Stack));
    stack->sizeOfstack = sizeOfstack;
    stack->top = -1;
    stack->array = (int* )malloc(stack->sizeOfstack * sizeof(int));
    return stack;
}

int iskFull(Stack *stack) {
    return stack->top == stack->sizeOfstack - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int item) {
    if (iskFull(stack)) {
        return;
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

int peek(Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

int BFS(int graph[][VERTICES], int startVertex, int endNode);
int edmondsKarp(int graph[][VERTICES], int startVertex, int endNode); // COPY PASTE
//int edmonds_karp_algo(Graph* graph, int s, int t);

int min(int num1, int num2) {
   return (num1 < num2) ? num1 : num2;
}

void init_graph(int graph[][VERTICES]) {
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            graph[i][j] = 0;
            flowPassed[i][j] = 0;
        }

    }
    //for (int i = 0; i < VERTICES; i++) {
        //parentsList[i] = -1;
        //currentPathCapacity[i] = 0;

        //printf("[%d]parentsList: %d\n", i, parentsList[i]);
        //printf("[%d]currentPathCapacity: %d\n", i, currentPathCapacity[i]);
    //}

}

void add_edge(int graph[][VERTICES], int vertex1, int vertex2, int weight) {
    graph[vertex1][vertex2] = weight;
}

void print_adjMatrix(int graph[][VERTICES]) {
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int adjMatrix[VERTICES][VERTICES];
    int parentsList[VERTICES];
    int currentPathCapacity[VERTICES];
    
    init_graph(adjMatrix);
    // Eksempler
    /*
    add_edge(adjMatrix, 0, 1, 16);
    add_edge(adjMatrix, 0, 2, 13);
    add_edge(adjMatrix, 1, 2, 10);
    add_edge(adjMatrix, 2, 1, 4);
    add_edge(adjMatrix, 1, 3, 12);
    add_edge(adjMatrix, 2, 4, 14);
    add_edge(adjMatrix, 3, 2, 9);
    add_edge(adjMatrix, 4, 3, 7);
    add_edge(adjMatrix, 3, 5, 20);
    add_edge(adjMatrix, 4, 5, 4);
    */
    add_edge(adjMatrix, 0, 1, 16);
    add_edge(adjMatrix, 0, 2, 13);
    add_edge(adjMatrix, 1, 2, 10);
    add_edge(adjMatrix, 2, 1, 6);
    add_edge(adjMatrix, 1, 3, 14);
    add_edge(adjMatrix, 3, 2, 7);
    add_edge(adjMatrix, 2, 4, 13);
    add_edge(adjMatrix, 4, 3, 8);
    add_edge(adjMatrix, 4, 5, 6);
    add_edge(adjMatrix, 3, 5, 18); // max flow skal være 24 // source: 0 sink: 5

    print_adjMatrix(adjMatrix);

    //printf("BFS: %d\n", BFS(adjMatrix, 0, 5));

    //adjMatrixOfGraph();

    printf("EDK: %d\n", edmondsKarp(adjMatrix, 0, 5));

    /*
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 0, 3, 1);

    addEdge(graph, 1, 2, 1);
    addEdge(graph, 2, 4, 1);
    */
    /*
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 2, 13);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 1, 6);
    addEdge(graph, 1, 3, 14);
    addEdge(graph, 3, 2, 7);
    addEdge(graph, 2, 4, 13);
    addEdge(graph, 4, 3, 8);
    addEdge(graph, 4, 5, 6);
    addEdge(graph, 3, 5, 18); // max flow skal være 24 // source: 0 sink: 5
    */
    /*
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1, 14);
    addEdge(graph, 2, 4, 10);
    addEdge(graph, 6, 7, 9);
    addEdge(graph, 5, 2, 10);
    addEdge(graph, 1, 4, 12);
    addEdge(graph, 2, 0, 15);
    addEdge(graph, 5, 3, 15); // max flow skal være 12 // source: 0 sink: 4
    //*/
    /*
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 2, 13);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 1, 4);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 4, 14);
    addEdge(graph, 3, 2, 9);
    addEdge(graph, 4, 3, 7);
    addEdge(graph, 3, 5, 20);
    addEdge(graph, 4, 5, 4); // max flow skal være 23 // source: 0 sink: 5
    */
    /*
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1, 11);
    addEdge(graph, 0, 2, 7);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 5, 3);
    addEdge(graph, 4, 5, 11); // max flow skal være 8 // source: 0 sink: 5
    */
    //printGraph(graph);
    
    //cleanVisitedArray(graph);
    //printf("BFS: ");
    //BFS(graph, 0, 5);
    //printf("Edmonds Karp: %d\n",edmonds_karp_algo(graph, 0, 5));  // Skift efter s og t


    return 0;
}
/*
int edmonds_karp_algo(Graph* graph, int s, int t) {
    Queue* prev = createQueue();                                    

    int flow;
    int maxFlow = 0;
    int i = 0;

    int currentNode = t;
    int prevNode = currentNode - 1;                                
    
    
    while (1) {

        flow = BFS(graph, s, t);
        printf("\n\nBFS Result: %d\n", flow);
        if (flow == 0) {
            break;
        }

        maxFlow += flow;
        while (currentNode != s) {
            enqueue(prev, currentNode);

            prevNode = dequeue(prev) - 1;

            //enqueue(prev, currentNode);
            //int prevNode = dequeue(prev);


            //flow += graph->adjList[currentNode]->weight;
            graph->adjList[currentNode]->weight += flow;

            //flow -= graph->adjList[prevNode]->weight;
            graph->adjList[prevNode]->weight -= flow;
           
            //currentNode = prevNode--;
            //currentNode = dequeue(prev) - 1;
            //break;
            currentNode = prevNode;
        }
        printf("Outflow: %d\n", flow);
        
    }
    return maxFlow;
}
*/

int BFS(int graph[][VERTICES], int startVertex, int endNode) {

    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));

    Stack* s = createStack(VERTICES);
    push(s, startVertex);

    parentsList[startVertex] = -2;

    currentPathCapacity[startVertex] = 999;

    while (!isEmpty(s)) {
        int currentVertex = s->top;
        pop(s);

        printf("TEST-1\n");

        int row = sizeof(graph[0]) / sizeof(graph[0][0]);
        for (int i = 0; i < VERTICES; i++) {

            printf("TEST-2\n");

            int to = i;
            
            printf("parentsList[to]: %d\n", parentsList[to]);

            if (parentsList[to] == -1) {
                
                printf("TEST-3\n");

                printf("graph[currentVertex][to]: %d\n", graph[currentVertex][to]);
                if (graph[currentVertex][to] - flowPassed[currentVertex][to] > 0) {               // Skal fixes

                    printf("TEST-4\n");

                    parentsList[to] = currentVertex;
                    printf("TEST 4.5 Pre-Beta\n");
                    currentPathCapacity[to] = min(currentPathCapacity[currentVertex], graph[currentVertex][to] - flowPassed[currentVertex][to]);

                    printf("TO: %d\n\n", to);
                    if (to == 5) {

                        printf("TEST-5\n");

                        return currentPathCapacity[endNode];
                    }
                    push(s, to);
                }
            }
        }
    }
    return 0;
}


int edmondsKarp(int graph[][VERTICES], int startVertex, int endNode)
{
   int maxFlow = 0;
   while(1)
   {
      int flow = BFS(graph, startVertex, endNode);
      if (flow == 0)
      {
         break;
      }
      maxFlow += flow;
      int currNode = endNode;
      while(currNode != startVertex)
      {
         int prevNode = parentsList[currNode];
         flowPassed[prevNode][currNode] += flow;
         flowPassed[currNode][prevNode] -= flow;
         currNode = prevNode;
      }
   }
return maxFlow;
}
