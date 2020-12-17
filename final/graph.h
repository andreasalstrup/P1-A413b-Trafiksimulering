#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int weight;
    struct node* next;
    struct node* prev;
} Node;

typedef struct graph {
    int numVertices;
    int* visited;
    Node** adjList;
} Graph;

Node* createNode(int val, int w) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->weight = w;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = (Node **)malloc(vertices * sizeof(Node));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {                                    /* Laver graf med knuder 0,1,2.. */
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int vertex1, int vertex2, int weight) {
    Node* newNode = createNode(vertex1, weight);

    newNode->next = graph->adjList[vertex2];                               /* Laver kant fra vertex1 til vertex2 */

    graph->adjList[vertex2] = newNode;

    //graph->adjList[vertex1]->prev = graph->adjList[vertex2];

    
    newNode = createNode(vertex2, weight);

    newNode->next = graph->adjList[vertex1];                               //Laver kant fra vertex2 til vertex1 
    newNode->prev = graph->adjList[vertex2];
    graph->adjList[vertex1] = newNode;

    //graph->adjList[vertex2]->prev = graph->adjList[vertex1];
    
}

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

void cleanVisitedArray(Graph* graph) {
    for (int i = 0; i < graph->numVertices + 1; i++) {
        graph->visited[i] = 0; 
    }
}