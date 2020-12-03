#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 4

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


void add_node(int s, int d, int c);
void print_list(void);

int main(void) {

    /* Allokere plads til alle nodes i tom naboliste */
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