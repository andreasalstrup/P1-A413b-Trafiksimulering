#include <stdio.h>
#include <stdlib.h>

struct queue {
    int nodes[20];
    int front;
    int rear;
};

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
    if (q->rear == 20 - 1) {
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
            q->front = q->rear = -1;
        }
    }
    return node;
}