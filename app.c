#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_NODE 10

/* Holder en knude */
typedef struct node {
    int vertexNum;                              /* Knudepunkt nummer */
    struct node *next;                          /* Holder adressen til næste node (vertex) */
    int capacity;                               /* Kapaciteten fra knudepunktet */
} node;

/* Graph struct */
struct graph {
    int vertexAmount;
    struct node** adjlists; 
    int* visited;
};

/* Prototyper */
struct node* createNode();
struct graph* createGraph();
int bfs();
void add_node();
int min();


int main(void) {
    struct graph* Graph = createGraph(MAX_NODE);
    struct graph* Graph1 = createGraph(MAX_NODE);
    struct graph* Graph2 = createGraph(MAX_NODE);

    /*  Uden Plusbus                */
    /*  S1 route 1                  */
    add_node(Graph, 0, 1, 480);
    add_node(Graph, 1, 2, 1760);
    add_node(Graph, 2, 3, 2800);

    /*  S1 route 2                  */
    add_node(Graph1, 0, 1, 640);
    add_node(Graph1, 1, 2, 3680);
    add_node(Graph1, 2, 3, 2640);
    add_node(Graph1, 3, 4, 1680);
    add_node(Graph1, 4, 5, 1280);
    add_node(Graph1, 5, 6, 2320);

    /*  S2 route 1                  */
    add_node(Graph2, 0, 1, 2720);
    add_node(Graph2, 1, 2, 3040);
    add_node(Graph2, 2, 3, 2000);
    add_node(Graph2, 3, 4, 1040);
    add_node(Graph2, 4, 5, 640);
    add_node(Graph2, 5, 6, 1680);
    /* Kapaciteten til afløb opbrugt */

    printf("BFS begins\n");
    int totalFlow = 0;

    int bfsRes = bfs(Graph, 0);
    printf("%4d\n\n", bfsRes);
    totalFlow += bfsRes;

    bfsRes = bfs(Graph1, 0);
    printf("%4d\n\n", bfsRes);
    totalFlow += bfsRes;

    bfsRes = bfs(Graph2, 0);
    printf("%4d\n\n", bfsRes);
    totalFlow += bfsRes;

    printf("\nMax Flow without Plusbus: %d\n\n\n", totalFlow);

    struct graph* Graphx = createGraph(MAX_NODE);
    struct graph* Graphx1 = createGraph(MAX_NODE);
    struct graph* Graphx2 = createGraph(MAX_NODE);
    struct graph* Graphx3 = createGraph(MAX_NODE);

    /*  Med Plusbus                 */
    /*  S1 route 1                  */
    add_node(Graphx, 0, 1, 480);
    add_node(Graphx, 1, 2, 4000);
    add_node(Graphx, 2, 3, 4000);

    /*  S1 route 2                  */
    add_node(Graphx1, 0, 1, 640);
    add_node(Graphx1, 1, 2, 4000);
    add_node(Graphx1, 2, 3, 4000);
    add_node(Graphx1, 3, 4, 4000);
    add_node(Graphx1, 4, 5, 3520);
    add_node(Graphx1, 5, 6, 3520);

    /*  S2 route 1                  */
    add_node(Graphx2, 0, 1, 2720);
    add_node(Graphx2, 1, 2, 3360);
    add_node(Graphx2, 2, 3, 3360);
    add_node(Graphx2, 3, 4, 3360);
    add_node(Graphx2, 4, 5, 2880);
    add_node(Graphx2, 5, 6, 2880);

    add_node(Graphx3, 0, 1, 720);
    add_node(Graphx3, 1, 2, 1520);
    add_node(Graphx3, 2, 3, 640);
    add_node(Graphx3, 3, 4, 640);
    add_node(Graphx3, 4, 5, 160);
    add_node(Graphx3, 5, 6, 160);
    /* Kapaciteten til afløb opbrugt */

    printf("BFS begins w/ Plusbus\n");
    totalFlow = 0;

    bfsRes = bfs(Graphx, 0);
    printf("%d\n\n", bfsRes);
    totalFlow += bfsRes;

    bfsRes = bfs(Graphx1, 0);
    printf("%d\n\n", bfsRes);
    totalFlow += bfsRes;

    bfsRes = bfs(Graphx2, 0);
    printf("%d\n\n", bfsRes);
    totalFlow += bfsRes;

    bfsRes = bfs(Graphx3, 0);
    printf("%d\n\n", bfsRes);
    totalFlow += bfsRes;

    printf("\nMax Flow with Plusbus: %d\n", totalFlow);

    return 0;
}

int bfs(struct graph* Graph, int startVertex) {
    struct queue* q = createQueue();
    int bottleneckValue = 0;

    Graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    int BFS_path[MAX_NODE]; /* Bliver aldrig brugt, men giver fejlen "stack smashing detected ***: terminated  Aborted" hvis den bliver fjernet. Grundlag er ukendt. */

    int path[] = {}; path[0] = 0;
    int pathCounter = 0;
    int lastVertex = 0;

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        struct node* temp = Graph->adjlists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertexNum;

            if (adjVertex != 0 && Graph->visited[adjVertex] == 0) {
                if (adjVertex > lastVertex) {
                    pathCounter++;
                    path[pathCounter] = adjVertex;
                }
                lastVertex = adjVertex;
            }

            if (Graph->visited[adjVertex] == 0) {
                Graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                printf("Vertex number: %2d  Capacity: %4d\n", adjVertex, temp->capacity);
            }
            temp = temp->next;
        }
    }

    printf("BFS Complete\n");
    for (int i = 0; i < pathCounter; i++) {
        int temp = path[i];
        if (i == 0) {
            bottleneckValue = Graph->adjlists[temp]->capacity;
        }
        bottleneckValue = min(Graph->adjlists[temp]->capacity, bottleneckValue);
    }

    printf("BottleneckValue: ");
    return bottleneckValue;
}

/* Tilføj node til graf, via naboliste */
void add_node(struct graph* Graph, int src, int dest, int c) {

    /* Tilføjer en kant fra knude "src" til knude "dest" */
    struct node* newNode = createNode(dest, c); /* Laver knuden "dest" */
    newNode->next = Graph->adjlists[src];
    Graph->adjlists[src] = newNode;

    /* Tilføjer en kant fra knude "dest" til knude "src" */
    newNode = createNode(src, 0); /* Laver knuden "src" */
    newNode->next = Graph->adjlists[dest];
    Graph->adjlists[dest] = newNode;
}

struct node* createNode(int v, int c) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertexNum = v;
    newNode->next = NULL;
    newNode->capacity = c;
    return newNode;
}

struct graph* createGraph(int vertices) {
    struct graph* graph = malloc(sizeof(struct graph));
    graph->vertexAmount = vertices;

    graph->adjlists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjlists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

int min(int num1, int num2) {
   return (num1 < num2) ? num1 : num2;
}

void cleanVisitedArray(struct graph* Graph) {
    for (int i = 0; i < Graph->vertexAmount + 1; i++) {
        Graph->visited[i] = 0; 
    }
}