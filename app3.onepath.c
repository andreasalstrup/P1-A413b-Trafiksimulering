#include <stdio.h>
#include <stdlib.h>

//DEBUG TOOL: valgrind --tool=memcheck --leak-check=yes -v --leak-check=full --show-reachable=yes ./test

#define MAX_NODE 6
#define CAPACITY 40                             //Placeholder value - Amount of nodes BFS has to run through  
#define MAX_PATH 20

/* Holder et hjørne */
typedef struct node {
    int vertexNum;                              // Knudepunkt nummer
    struct node *next;                          // Holder adressen til næste node (vertex)
    int capacity;                               // Kapaciteten fra knudepunktet
    int deadNodeToken;
    int visitedOnce;
} node;

/* Queue struct */
struct queue {
    int nodes[CAPACITY];
    int front;
    int rear;
};

/* Graph struct */
struct graph {
    int vertexAmount;
    struct node** adjlists; 
    int* visited;
};

/* Queue prototypes */
struct queue* createQueue();
struct node* createNode();
struct graph* createGraph();
void enqueue();
int dequeue();
int isEmpty();
int bfs();
int min();
void add_node();
void cleanVisitedArray();
//int edmonds_karp_algo();
/* End of queue prototypes */

int main(void) {

    struct graph* Graph = createGraph(MAX_NODE); 
    struct graph* Graph1 = createGraph(MAX_NODE);

    add_node(Graph, 0, 1, 16);
    add_node(Graph, 1, 2, 10);
    add_node(Graph, 1, 3, 12);
    add_node(Graph, 3, 5, 20);
    //Flow should be 12 here

    add_node(Graph1, 0, 2, 13);
    add_node(Graph1, 2, 4, 14);
    add_node(Graph1, 4, 5, 4);
    //Flow should be 4 here

    printf("BFS begins\n");

    int totalFlow = 0;

    int bfsRes = bfs(Graph, 0, 1);
    printf("%d\n", bfsRes);
    cleanVisitedArray(Graph);

    totalFlow += bfsRes;

    bfsRes = bfs(Graph1, 0, 0);
    printf("%d\n", bfsRes);

    totalFlow += bfsRes;

    printf("Max Flow: %d\n", totalFlow);
    //Total max should be 16

    return 0;
}

/* Tilføj node til graf, via naboliste */
void add_node(struct graph* Graph, int src, int dest, int c) {

    //Adds edge from src to dest
    struct node* newNode = createNode(dest, c); //makes the dest node
    newNode->next = Graph->adjlists[src];
    Graph->adjlists[src] = newNode;

    //Adds edge from dest to src
    newNode = createNode(src, 0); //makes the src node
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

int bfs(struct graph* Graph, int startVertex, int firstRunToken) {
    
    int bottleneckValue = 0;
    struct queue* q = createQueue();

    Graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    int BFS_path[MAX_NODE]; //Can't remove, causes stack smashing for whatever reason

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
                    printf("--- adjVertex: %d -- lastVertex: %d ---\n", adjVertex, lastVertex);
                    pathCounter++;
                    path[pathCounter] = adjVertex;
                }
                lastVertex = adjVertex;
            }

            if (Graph->visited[adjVertex] == 0 && Graph->adjlists[adjVertex]->capacity != 0) {
                Graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                printf("Curr_Vertex: %d  Capacity: %d\n", adjVertex, temp->capacity);
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

    for (int i = 0; i < pathCounter; i++) {
        int temp = path[i];
        Graph->adjlists[temp]->capacity -= bottleneckValue;
        printf("New Capacity: %d  For Vertex: %d\n", Graph->adjlists[temp]->capacity, temp);
    }

    printf("Bottleneck calculated and Capacity adjusted. Returning..\n");

    return bottleneckValue;
}

int min(int num1, int num2) {
   return (num1 < num2) ? num1 : num2;
}

void cleanVisitedArray(struct graph* Graph) {
    for (int i = 0; i < Graph->vertexAmount + 1; i++) {
        Graph->visited[i] = 0; 
    }
}

struct graph* createGraph(int vertices) {
    struct graph* graph = malloc(sizeof(struct graph));
    graph->vertexAmount = vertices;

    graph->adjlists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjlists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}


struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if (q->rear == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

void enqueue(struct queue* q, int value) {
    if (q->rear == CAPACITY - 1) {
        printf("\nQueue is full");
    }
    else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->nodes[q->rear] = value;
    }
}

int dequeue(struct queue* q) {
    int node;
    if (isEmpty(q)) {
        printf("Queue is empty");
        node = -1;
    }
    else {
        node = q->nodes[q->front];
        q->front++;
        if (q->front > q->rear) {
            //printf("Resetting queue\n");
            q->front = q->rear = -1;
        }
    }
    return node;
}

/*
int edmonds_karp_algo(int s, int t) {
    node *p = adjlist[t]->head;
    int currentNode, prevNode;
    int flowPassed[MAX_NODE][MAX_NODE];
    int flow;
    int maxFlow = 0;
    
    while (1) {
        //flow = bfs(s, t); //To be researched
        if (flow == 0) break;

        maxFlow += flow;
        currentNode = t;

        while (currentNode != s) {
            prevNode = p[currentNode - 1].vertexNum;
            flowPassed[prevNode][currentNode] += flow;
            flowPassed[currentNode][prevNode] -= flow;
            currentNode = prevNode;
        }
    }
    return maxFlow;
}
*/