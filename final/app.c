#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"

int BFS(Graph* graph, int startVertex, int endNode);
int edmonds_karp_algo(Graph* graph, int s, int t);

int main() {

    // Eksempler

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

   
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1, 11);
    addEdge(graph, 0, 2, 7);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 5, 3);
    addEdge(graph, 4, 5, 11); // max flow skal være 8 // source: 0 sink: 5
    
    printGraph(graph);
    
    //cleanVisitedArray(graph);
    //printf("BFS: ");
    //BFS(graph, 0, 5);
    printf("Edmonds Karp: %d\n",edmonds_karp_algo(graph, 0, 5));  // Skift efter s og t

    return 0;
}

int edmonds_karp_algo(Graph* graph, int s, int t) {
    Queue* prev = createQueue();                                    /* rebuild augmented path - 3:50 https://www.youtube.com/watch?v=OViaWp9Q-Oc */

    int flow;
    int maxFlow = 0;
    int i = 0;

    int currentNode = t;
    int prevNode = currentNode - 1;                                 /* prevNode muligvis fejlen */
    
    
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

int BFS(Graph* graph, int startVertex, int endNode) {
    Queue* q = createQueue();
    Queue* prev = createQueue();                                                            /* Laver prev kø */

    //int *neighborHistory;

    int currentPathCapacity;
    if (graph->visited[startVertex] == 0 /*&& (graph->adjList[startVertex]->weight >= 0)*/) {
        graph->visited[startVertex] = 1;
        currentPathCapacity = graph->adjList[startVertex]->weight;
        //enqueue(prev, startVertex);
    } 
    enqueue(q, startVertex);
    while (!isEmpty(q)) {
        //printQueue(q);
        int currentVertex = dequeue(q);
        printf("%d[%d] ", currentVertex, graph->adjList[currentVertex]->weight);                                                      /* Tilføjes til prev kø */

        enqueue(prev, currentVertex);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int neighbor = temp->data;

            //printf("\nBEFORE VISITED: %d Vertex[%d]\n", graph->visited[neighbor], graph->adjList[currentVertex]->data);

            if (graph->visited[neighbor] == 0 && (graph->adjList[neighbor]->weight >= 0)) {
                graph->visited[neighbor] = 1;
                enqueue(q, neighbor);
            }                    
            
            if (currentPathCapacity > graph->adjList[currentVertex]->weight ) {
                if (graph->adjList[currentVertex]->weight > 0) {
                    currentPathCapacity = graph->adjList[currentVertex]->weight;
                }
                

                    printQueue(prev);
                    while (!isEmpty(prev)) {
                        //graph->adjList[startVertex]->weight += currentPathCapacity;
                        int currentPrev = dequeue(prev);
                        printf("\nBefore[%d]\n", graph->adjList[currentPrev]->weight);
                        //printf("   prev = %d   ", currentPrev);
                        graph->adjList[currentPrev]->weight -= currentPathCapacity; /* Sætter min kapacitet til knuder i prev kø */
                         
                        printf("After[%d]\n", graph->adjList[currentPrev]->weight);

                        if (graph->adjList[currentPrev]->weight >= 0) {
                            graph->visited[currentPrev] = 1;
                        }
                    }
                    
                    cleanVisitedArray(graph);
                    return currentPathCapacity;
                }
            }
            temp = temp->next;
        }
    }
    return 0;
}