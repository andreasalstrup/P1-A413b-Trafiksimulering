#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
//#include "queue.h"
#include "graph.h"
#include "c-vector-master/vec.h"

#define VERTICES 10

int capacities[VERTICES][VERTICES];

int flowPassed[VERTICES][VERTICES];

int parentsList[VERTICES];

int currentPathCapacity[VERTICES];

typedef struct vector_array {
    int* to;
} vectorArr;


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

int BFS();
int edmondsKarp(); // COPY PASTE
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

void add_edge(vectorArr *graph, int vertex1, int vertex2, int weight) {
    vector_add(&graph[vertex1].to, vertex2);
    vector_add(&graph[vertex2].to, vertex1);
    capacities[vertex1][vertex2] = weight;
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
    vectorArr graph[VERTICES];
    for (int i = 0; i < VERTICES; i++) {
        graph[i].to = vector_create();
    }

    //vector_add(&graph[0].to, 2);
    //printf("Vector Print: %d\n", arr_vec[0].to[0]);
    
    //init_graph(adjMatrix);
    // Eksempler

    add_edge(graph, 0, 1, 16);
    add_edge(graph, 0, 2, 13);
    add_edge(graph, 1, 2, 10);
    add_edge(graph, 2, 1, 6);
    add_edge(graph, 1, 3, 14);
    add_edge(graph, 3, 2, 7);
    add_edge(graph, 2, 4, 13);
    add_edge(graph, 4, 3, 8);
    add_edge(graph, 4, 5, 6);
    add_edge(graph, 3, 5, 18); // max flow skal være 24 // source: 0 sink: 5

    //print_adjMatrix(adjMatrix);

    //printf("BFS: %d\n", BFS(adjMatrix, 0, 5));

    //adjMatrixOfGraph();

    printf("EDK: %d\n", edmondsKarp(graph, 0, 5));
    
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

int BFS(vectorArr *graph, Stack *s, int startVertex, int endNode) {

    //memset(parentsList, -1, sizeof(parentsList));
    //memset(currentPathCapacity, 0, sizeof(currentPathCapacity));

    for (int i = 0; i < sizeof(parentsList); i++) {
        parentsList[i] = -1;
        currentPathCapacity[i] = 0;

        printf("[%d]parentsList: %d\n", i, parentsList[i]);
        printf("[%d]currentPathCapacity: %d\n", i, currentPathCapacity[i]);
    }

    //Stack* s = createStack(VERTICES);
    push(s, startVertex);

    parentsList[startVertex] = -2;

    currentPathCapacity[startVertex] = 999;

    while (!isEmpty(s)) {
        int currentVertex = s->top;
        pop(s);

        printf("TEST-1\n");

        printf("vector_size(graph->to[currentVertex]: %ld\n", vector_size(graph[currentVertex].to));
        for (int i = 0; i < vector_size(graph[currentVertex].to); i++) {

            printf("TEST-2\n");

            int to = graph[currentVertex].to[i];
            printf("currentVertex: %d\n", currentVertex);
            printf("TO-1: %d\n", to);
            printf("parentsList[to]: %d\n", parentsList[to]);

            if (parentsList[to] == -1) {
                
                printf("TEST-3\n");

                printf("graph[currentVertex][to]: %d\n", capacities[currentVertex][to]);
                if (capacities[currentVertex][to] - flowPassed[currentVertex][to] > 0) {              

                    printf("TEST-4\n");

                    parentsList[to] = currentVertex;
                    printf("TEST 4.5 Pre-Beta\n");
                    currentPathCapacity[to] = min(currentPathCapacity[currentVertex], capacities[currentVertex][to] - flowPassed[currentVertex][to]);

                    printf("TO-2: %d\n\n", to);
                    if (to == endNode) {

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


int edmondsKarp(vectorArr *graph, int startVertex, int endNode) {

    Stack* s = createStack(VERTICES);

   int maxFlow = 0;
   while(1) { 
      int flow = BFS(graph, s, startVertex, endNode);
      printf("FLOW: %d\n", flow);
      if (flow == 0)
      {
         break;
      }
      maxFlow += flow;
      int currNode = endNode;
      while(currNode != startVertex)
      {
         int prevNode = parentsList[currNode];
         printf("prevNode: %d\n", prevNode);
         flowPassed[prevNode][currNode] += flow;
         flowPassed[currNode][prevNode] -= flow;
         currNode = prevNode;
      }
   }
return maxFlow;
}
