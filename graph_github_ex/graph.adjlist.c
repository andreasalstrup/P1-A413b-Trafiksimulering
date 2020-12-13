#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * node: piece of data containing a data field and a pointer to the next node of the list
*/
struct node {
    int data;
    int weight;
    struct node* next;
};

typedef struct node Node;

/**
 * graph: a graph with a set number of vertices, a pointer to a linked list and a pointer to an helper array used to traverse the graph
*/
struct graph {
    int numVertices;
    int* visited;
    Node** adjList; // pointer to struct node*
};

typedef struct graph Graph;

/**
 * createNode: creates a node given a numeric value
 * @param val numeric value
 * @return pointer to the newly created node
*/
Node* createNode(int val, int w) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->weight = w;
    newNode->next = NULL;

    return newNode;
}

/**
 * createGraph: creates a graph given a number of vertices where, for simplicity, vertices are identified by their indices
 * @param vertices number of vertices
 * @return pointer to the newly created graph
*/
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices * sizeof(Node));
    graph->visited = malloc(vertices * sizeof(int));

    /*
        For simplicity, we use an unlabeled graph as opposed to a labeled one 
        i.e. the vertices are identified by their indices 0,1,2,3.
    */
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

/**
 * addEdge: creates a conection between two vertices
 * @param graph a graph structure
 * @param vertex1 a numeric value for the first vertex
 * @param vertex2 a numeric value for the second vertex
 * @return void
*/
void addEdge(Graph* graph, int vertex1, int vertex2, int weight) {
    Node* newNode = createNode(vertex1, weight);

    // add edge from vertex1 to vertex2
    newNode->next = graph->adjList[vertex2];
    graph->adjList[vertex2] = newNode;

    newNode = createNode(vertex2, weight);

    // add edge from vertex2 to vertex1
    newNode->next = graph->adjList[vertex1];
    graph->adjList[vertex1] = newNode;
}

/**
 * printGraph: prints the given graph by iterating trough it
 * @param graph a graph structure
 * @return void
*/
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjList[v];
        printf("\n Vertex %d: \n", v);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * DFS: recursive depth first search implementation
 * @param graph a graph structure
 * @param vertex the numeric value of the node you want to start traversin from
 * @return void
*/
void DFS(Graph* graph, int startVertex) {
    Node* nodeAndNeighbors = graph->adjList[startVertex];
    Node* temp = nodeAndNeighbors;

    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp) {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }

}

/**
 * BFS: iterative breadth first search implementation
 * @param graph a graph structure
 * @param startVertex the starting vertex
 * @return void 
*/
int BFS(Graph* graph, int startVertex, int endNode) {
    Queue* q = createQueue();
    int currentPathCapacity = 999;

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        // printQueue(q);
        int currentVertex = dequeue(q);
        printf("%d w:%d ", currentVertex, graph->adjList[currentVertex]->weight);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int neighbor = temp->data;

            if (graph->visited[neighbor] == 0) {
                graph->visited[neighbor] = 1;
                enqueue(q, neighbor);
            }
            //printf("%d ", currentPathCapacity);
            if (currentPathCapacity > graph->adjList[currentVertex]->weight) {
                currentPathCapacity = graph->adjList[currentVertex]->weight;
            }
            temp = temp->next;

            if (graph->adjList[currentVertex]->data == endNode) {
                return graph->adjList[endNode]->weight;
            }
        }
    }
    return currentPathCapacity;
    //printf("\n");
    //printf("%d\n", currentPathCapacity);
}

/**
 * cleanVisitedArray: re-set the values back to 0 so we can DFS again
 * @param graph a graph structure
 * @return void
*/
void cleanVisitedArray(Graph* graph) {
    for (int i = 0; i < graph->numVertices + 1; i++) {
        graph->visited[i] = 0; 
    }
}

int edmonds_karp_algo(Graph* graph, int s, int t) {
    int flow;
    int maxFlow = 0;
    
    while (1) {
        flow = BFS(graph, s, t); //To be researched
        printf("\n\nBFS Result: %d\n", flow);
        if (flow == 0) {
            break;
        }

        maxFlow += flow;
        int currentNode = t;
        while (currentNode != s) {
            //int prevNode = graph->adjList[currentNode]->data;
            int prevNode = graph->numVertices--;
            flow += graph->adjList[prevNode]->weight;
            flow -= graph->adjList[currentNode]->weight;
            
            //flowPassed[prevNode][currentNode] += flow;
            //flowPassed[currentNode][prevNode] -= flow;
            printf("prevNode: %d\n", prevNode);
            currentNode = prevNode;
        }
        
    }
    return maxFlow;
}

int main() {
    /*
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 0, 3, 1);

    addEdge(graph, 1, 2, 1);
    addEdge(graph, 2, 4, 1);
    */
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
    addEdge(graph, 3, 5, 18); // max flow skal være 24


    printGraph(graph);
    
    printf("\nDFS: ");
    DFS(graph, 0);
    printf("\n");

    cleanVisitedArray(graph);

    printf("BFS: ");
    BFS(graph, 0, 5);
    printf("Edmonds Karp: %d\n",edmonds_karp_algo(graph, 0, 5));

    return 0;
}