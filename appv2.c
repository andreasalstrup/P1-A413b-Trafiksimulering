#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 5
#define CAPACITY 40                             //Placeholder value - Amount of nodes BFS has to run through

/* Holder et hjørne */
typedef struct node {
    int vertexNum;                              // Knudepunkt nummer
    struct node *next;                          // Holder adressen til næste node (vertex)
    int capacity;                               // Kapaciteten fra knudepunktet
    int visited;
} node;

/* Holder adressen til den første node i listen */
/* headnode holder alle nabo nodes              */
typedef struct list {
    node *head;
} list;

/* Liste med adressen til headnodes */
/* Initialiseret til 0              */
list *adjlist[MAX_NODE] = {0};

/* Queue struct */
typedef struct queue {
    int nodes[CAPACITY];
    int front;
    int rear;
} queue;

/* Graph struct */
typedef struct graph {
    int vertexNum;
    struct node** adjlist; //Should maybe point to *adjlist. Subject to change
    int visited[MAX_NODE];
} graph;

/* Queue prototypes */
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
/* End of queue prototypes */

void add_node(int s, int d, int c);
void print_list(void);
int edmonds_karp_algo(struct graph *graph, int s, int t);
int bfs2(struct graph *graph, int s, int t);
int min(int num1, int num2);

int main(void) {
    graph *graph = malloc(sizeof(struct graph));

    /* Laver graf                                    */
    /* allokere plads til alle nodes i tom naboliste */
    for (int i = 0; i < MAX_NODE; i++) {
        adjlist[i] = (list *)malloc(sizeof(list));
        adjlist[i]->head = NULL;
    }

    add_node(0, 1, 16);
    add_node(0, 2, 13);
    add_node(1, 2, 10);
    add_node(2, 1, 6);
    add_node(1, 3, 14);
    add_node(3, 2, 7);
    add_node(2, 4, 13);
    add_node(4, 3, 8);
    add_node(4, 5, 6);
    add_node(3, 5, 18); // max flow skal være 24
    

    

    print_list();

    printf("%d",edmonds_karp_algo(graph, 0, 3));

    /* Testing */
    node *p = adjlist[0]->head;
    printf("\n[%d,%dw]\n", p->next->vertexNum, p->next->capacity);
    return 0;
}

/* Tilføj node til graf, via naboliste */
void add_node(int s, int d, int c) {
    node *dest, *tmp, *src;

    if (adjlist[s]->head == NULL) {         
        src = (node *)malloc(sizeof(node));     // laver node, source variabel opbevare adressen 
        src->vertexNum = s;                     // gir vertexNum værdien s i source node
        src->next = NULL;                       // gir next værdien NULL i source node
        src->capacity = 0;                      // Sætter src node til 0 (skal måske havde en maksværdi)
        adjlist[s]->head = src;                 // gemmer indholdet i source, i adjlist index s 
    }

    dest = (node *)malloc(sizeof(node));        // laver ny node, destinations variabel opbebare adressen
    dest->vertexNum = d;                        // gir vertexNum værdien d i dest node
    dest->next = NULL;                          // gir next værdien NULL i dest node
    dest->capacity = c;                         // Sætter kapaciteten mellem src og dest node
    tmp = adjlist[s]->head;                     // tmp variabel assignes værdien i head i adjlist[s]
    
    while (tmp->next != NULL) {
        tmp = tmp->next;                        // hvis næste node ikke er NULL assignes tmp værdien til næste nodes værdi
    }
    tmp->next = dest;                           // gemmer indholdet i destinations variablen, i næste node
}

/* Print visuel repræsentation af hvordan nodes er forbundet i nabolisten */
void print_list(void) {
    for (int i = 0; i < MAX_NODE; i++) {
        node *p = adjlist[i]->head;
        printf("\n Vertex %d: ", i);

        while (p) {
            printf("[%d,%dw] -> ", p->vertexNum, p->capacity);
            p = p->next;
        }
    printf("\n");
    }
}

int edmonds_karp_algo(struct graph *graph, int s, int t) {
    node *p = adjlist[t]->head;
    int currentNode, prevNode;
    int flowPassed[MAX_NODE][MAX_NODE];
    int flow;
    int maxFlow = 0;
    
    while (1) {
        printf("Test1\n");
        flow = bfs2(graph, s, t); //To be researched
        printf("Test2: %d\n", flow);
        if (flow == 0) break;

        maxFlow += flow;
        currentNode = t;
        printf("Test3\n");
        while (currentNode != s) {
            prevNode = p[currentNode - 1].vertexNum;
            flowPassed[prevNode][currentNode] += flow;
            flowPassed[currentNode][prevNode] -= flow;
            currentNode = prevNode;
        }
        
    }
    return maxFlow;
}

int bfs2(struct graph *graph, int s, int t) {
    int capacities[MAX_NODE][MAX_NODE];
    int flowPassed[MAX_NODE][MAX_NODE];

    queue* q = createQueue();
    enqueue(q, s);

    printf("BFS Test 1\n");

    int currentPathCapacity[MAX_NODE];

    printf("BFS Test 2\n");
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));
    currentPathCapacity[s] = 999;

    printf("BFS Test 3\n");

    for (int i = 0; i < MAX_NODE; i++) {
        graph[s].visited[i] = -1;
    }
    printf("BFS Test 4\n");
    while(!isEmpty(q)){

        int currentNode = q->front;
        dequeue(q);

        printf("BFS Test 5\n");
        for(int i = 0; i < graph[currentNode].vertexNum; i++) {

            int to_node = graph[currentNode].adjlist[i]->next->vertexNum;
            printf("BFS Test 5\n");
            if(graph[s].visited[to_node] == -1) {
                printf("BFS Test 6\n");
                if(capacities[currentNode][to_node] - flowPassed[currentNode][to_node] > 0) {

                    graph[s].visited[to_node] = currentNode;
                    currentPathCapacity[to_node] = min(currentPathCapacity[currentNode], capacities[currentNode][to_node] - flowPassed[currentNode][to_node]);
                    printf("BFS Test 7\n");
                    if(to_node == t) {

                        return currentPathCapacity[t];

                    }

                    enqueue(q, to_node);

                }
            }
        }
    }
    return 0;
}

int min(int num1, int num2) {
   return (num1 < num2) ? num1 : num2;
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
            printf("Resetting queue\n");
            q->front = q->rear = -1;
        }
    }
    return node;
}
