#include <stdio.h>

#define A 0
#define B 1
#define C 2
#define MAX_NODES 1000
#define O 1000000000

int n;
int e;
int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) {
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = C;
  return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < n; u++) {
    color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < n; v++) {
      if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == C;
}

// Applying fordfulkerson algorithm
int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      flow[i][j] = 0;
    }
  }

  // Updating the residual values of edges
  while (bfs(source, sink)) {
    int increment = O;
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    // Adding the path flows
    max_flow += increment;
  }
  return max_flow;
}

int main() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      capacity[i][j] = 0;
    }
  }
  n = 6;
  e = 7;

  capacity[0][1] = 16;
  capacity[0][2] = 13;
  capacity[1][2] = 10;
  capacity[2][1] = 6;
  capacity[1][3] = 14;
  capacity[3][2] = 7;
  capacity[2][4] = 13;
  capacity[4][3] = 8;
  capacity[4][5] = 6;
  capacity[3][5] = 18;

    /*
  add_edge(graph, 0, 1, 16);
    add_edge(graph, 0, 2, 13);
    add_edge(graph, 1, 2, 10);
    add_edge(graph, 2, 1, 6);
    add_edge(graph, 1, 3, 14);
    add_edge(graph, 3, 2, 7);
    add_edge(graph, 2, 4, 13);
    add_edge(graph, 4, 3, 8);
    add_edge(graph, 4, 5, 6);
    add_edge(graph, 3, 5, 18); // max flow skal være 24 // source: 0 sink: 5
    */
  int s = 0, t = 5;
  printf("Max Flow: %d\n", fordFulkerson(s, t));
}