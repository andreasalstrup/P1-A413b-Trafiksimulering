#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 4
#define CAPACITY 40                             //Placeholder value - Amount of nodes BFS has to run through

/* Holder et hjørne */
typedef struct node {
    int vertexNum;                              // Knudepunkt nummer
    struct node *next;                          // Holder adressen til næste node (vertex)
    int capacity;                               // Kapaciteten fra knudepunktet
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
struct queue {
    int nodes[CAPACITY];
    int front;
    int rear;
};

/* Graph struct */
struct graph {
    int vertexNum;
    struct node** adjlist; //Should maybe point to *adjlist. Subject to change
    int* visited;
};

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
int edmonds_karp_algo(int s, int t);

int main(void) {

    /* Laver graf                                    */
    /* allokere plads til alle nodes i tom naboliste */
    for (int i = 0; i < MAX_NODE; i++) {
        adjlist[i] = (list *)malloc(sizeof(list));
        adjlist[i]->head = NULL;
    }

    add_node(0, 1, 5);
    add_node(0, 2, 10);
    add_node(0, 3, 15);

    add_node(1, 0, 5);
    add_node(1, 2, 15);

    add_node(2, 0, 5);
    add_node(2, 1, 10);
    add_node(2, 3, 15);

    add_node(3, 0, 50);
    add_node(3, 2, 500);

    print_list();

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
        printf("\n Vetex %d\n: ", i);

        while (p) {
            printf("[%d,%dw] -> ", p->vertexNum, p->capacity);
            p = p->next;
        }
    printf("\n");
    }
}

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

int bfs(struct graph* graph, int startVertex, int t) {
    struct queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        //Printqueue
        int currentVertex = dequeue(q);
        //printf("Visited %d\n", currentVertex);
        struct node* temp = graph->adjlist[currentVertex];

        while (temp) {
            int adjVertex = temp->vertexNum;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

/*
struct graph* createGraph(int vertices) {

}
*/

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
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return node;
}