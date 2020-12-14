#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 4
#define CAPACITY 40                             //Placeholder value - Amount of nodes BFS has to run through
#define MAX_PATH 20

/* Holder et hjørne */
struct node {
    int vertexNum;                              // Knudepunkt nummer
    struct node *next;                          // Holder adressen til næste node (vertex)
    int capacity;                               // Kapaciteten fra knudepunktet
};

/* Holder adressen til den første node i listen */
/* headnode holder alle nabo nodes              */

/*
typedef struct list {
    node *head;
} list;
*/

/* Liste med adressen til headnodes */
/* Initialiseret til 0              */
//list *adjlist[MAX_NODE] = {0};

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

struct path {
    struct node vertex;
};

/* Queue prototypes */
struct queue* createQueue();
struct node* createNode();
struct graph* createGraph();
void enqueue();
int dequeue();
int isEmpty();
int bfs();
void reverse();
/* End of queue prototypes */

void add_node();
void print_list();
int edmonds_karp_algo();

int main(void) {

    /* Laver graf                                    */
    /* allokere plads til alle nodes i tom naboliste */
    /*
    for (int i = 0; i < MAX_NODE; i++) {
        adjlist[i] = (list *)malloc(sizeof(list));
        adjlist[i]->head = NULL;
    }
    */

    struct graph* Graph = createGraph(MAX_NODE);

    add_node(Graph, 0, 1, 5);
    add_node(Graph, 0, 2, 10);
    add_node(Graph, 0, 3, 15);

    add_node(Graph, 1, 0, 5);
    add_node(Graph, 1, 2, 15);

    add_node(Graph, 2, 0, 5);
    add_node(Graph, 2, 1, 10);
    add_node(Graph, 2, 3, 15);

    add_node(Graph, 3, 0, 10);
    add_node(Graph, 3, 2, 10);

    //print_list();

    /* Testing */
    //node *p = adjlist[0]->head;
    //printf("\n[%d,%dw]\n", p->next->vertexNum, p->next->capacity);

    int bfsRes = bfs(Graph, 0, 0, 3);

    printf("%d\n", bfsRes);
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

/*
//Print visuel repræsentation af hvordan nodes er forbundet i nabolisten 
void print_list(void) {
    for (int i = 0; i < MAX_NODE; i++) {
        node *p = adjlist[i]->head;
        printf("\n Vetex %d\n: ", i);

        while (p) {
            printf("[%d,%dw] -> ", p->vertexNum, p->capacity);
            p = p->next;
        }
    printf("\n");
    }
}
*/

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

int bfs(struct graph* Graph, int startVertex, int s, int t) {
    
    int flowCapacity = 0;
    struct queue* q = createQueue();

    Graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    int BFS_path[MAX_PATH];
    int count = 0;
    BFS_path[count] = 0;

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        struct node* temp = Graph->adjlists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertexNum;

            if (Graph->visited[adjVertex] == 0) {
                Graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                count++;
                BFS_path[count] = adjVertex;
                flowCapacity += temp->capacity;
            }
            
            temp = temp->next;
        }
    }

    
    //Recontructing the path in reverse
    count = 0;
    int* path[] = { NULL };
    for(int at = t; at != 0; at = BFS_path[at]) {
        path[count];
        count++;
    }

    //Reversing the path
    int n = sizeof(path)/sizeof(path[0]);
    reverse(path, n);

    for (int i = 0; i < sizeof(path); i++) {
        //int temp = path[i];
        
    }

    return flowCapacity;
}

void reverse(int array[], int n) {
    int aux[n];

    for (int i = 0; i > n; i++) {
        aux[n-1-i] = array[i];
    }

    for (int i = 0; i < n; i++) {
        array[i] = aux[i];
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