/* C implementation of Edmonds Karp Algorithm and Adjacency List*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#pragma region EdmonsKarpExample(ClassReplacer)

struct Edge {
    int from, to;
    long flow;
    long capacity; /* If Residual, set Capacity = 0 */
    int edge_identifier; /* 1 = Normal Edge, 0 = Residual */
};

void Edge(int from, int to, long capacity) {
    this.from = from;
    this.to = to;
    this.capacity = capacity;
}

long remainingCapacity(long capacity, long flow) {
    return capacity - flow;
}

void augment (long bottleNeck, long flow, long residual_flow) {
    flow += bottleNeck;
    residual_flow -= bottleNeck;
}

#pragma endregion

#pragma region NetworkFlowSolverBase

long INF = LONG_MAX / 2;

int n, s, t;

int visitedToken = 1;
int visited[];

//bool solved

long maxFlow;

//Adjacency list goes below
//List<Edge>[] graph;

void NetworkFlowSolverBase(int n, int s, int t, int visited[]) {
    n = n;
    s = s;
    t = t;
    InitializeEmptyFlowGraph(n);
    //visited = new int[n];
}

void InitializeEmptyFlowGraph(int n) {
    //graph = new List[n];
    for (int i = 0; i < n; i++) {
        //graph[i] = new ArrayList<Edge>();
    }
}

void AddEdge(int from, int to, long capacity) {
    //if (capacity <= 0)
      //throw exception IllegalArgumentException("Foward edge capacity <= 0"); Not possible in C tho

    //Edge e1 = new Edge(from, to, capacity);
    //Edge e2 = new Edge(to, from, 0);
    //e1.residual = e2;
    //e2.residual = e1;
    //graph[from].add(e1);
    //graph[to].add(e2);
}

/* List<Edge>[] getGraph() {
    execute();
    return maxFlow;
} */

void visit(int i) {
    visited[i] = visitedToken;
}

/* bool visited(int i) {
    return visited[i] == visitedToken;
} */

void markAllNodesAsUnvisited() {
    visitedToken++;
}

void execute() {
    /* if (solved) return;
    solved = true;
    solve();
    */
}

#pragma endregion

#pragma region EdmondsKarpSolver

void EdmondsKarpSolver(int n, int s, int t) {
    //super(n, s, t);
}

//Run Edmonds-Karp and compute the max flow fromthe source to the sink node
void solve() {
    long flow;
    do {
        markAllNodesAsUnvisited();
        flow = bfs();
        maxFlow += flow;
    } while (flow !=0);
}

long bfs() {
    //Queue<Integer> q = new ArrayDeque<>(n);
    visit(s);
    //q.offer(s);

    /*Edge prev[] = new Edge[n];
    while(!q.isEmpty()) {
        int node = q.poll();
        if (node == t) break;

        for (Edge edge : graph[node]) {
            long cap = edge.remainingCapacity();
            if (cap > 0 && !visited(edge.to)) {
                visit(edge.to);
                prev[edge.to] = edge;
                q.offer(edge.to);
            }


        } 
    } */

}

//if (prev[t] == null) return 0;

long bottleNeck = LONG_MAX;
/* for(Edge edge = frev[t]; edge != null; edge = prev[edge.from])
    bottleNeck = min(bottleNeck, edge.remainingCapacity());

    for(Edge edge = prev[t]; edge != null; edge = prev[edge.from])
        edge.augment(bottleNeck);

        return bottleNeck;
*/

#pragma endregion

int main(void) {
    //n is the number of nodes in total -> Including Source and Sink
    int n = 10;

    int s = n-2; //Source
    int t = n-1; //Sink

    //NetworkFlowSolverBase solver = new EdmondskarpSolver(n, s, t);

    //Adding Edges

    /*
    Edges from source
    solver.addEdge(s, 0, 5);
    solver.addEdge(s, 1, 10);
    solver.addEdge(s, 2, 5);

    Mid Edges
    solver.addEdge(0, 3, 10);
    solver.addEdge(1, 0, 15);
    solver.addEdge(1, 4, 15);

    Edges to sink
    solver.addEdge(0, t, 5);
    solver.addEdge(4, t, 15);
    solver.addEdge(3, t, 10);
    */

    //Prints
    /*
    prinf("Maximum Flow is: %d\n", solver.getMaxFlow());

    List<Edge>[] resultGraph = solver.getGraph();

    //Display all edges part of the resulting residual graph
    for (List<Edge> edges : resultGraph)
        for (Edge e : edges)
            printf(e.toString(s, t));

    //toString(s, t) does not exist right now
    */
}