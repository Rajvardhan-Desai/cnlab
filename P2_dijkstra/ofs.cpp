#include <iostream>
using namespace std;

#define INF 9999
#define N 5              // number of routers/nodes

int main() {
    // Cost adjacency matrix for the given network
    // Change these values according to the network given by instructor
    int cost[N][N] = {
        {0,   10,  3,   INF, INF},
        {10,  0,   1,   2,   INF},
        {3,   1,   0,   8,   2},
        {INF, 2,   8,   0,   7},
        {INF, INF, 2,   7,   0}
    };

    int dist[N];      // shortest distance from source
    int visited[N];   // visited flag
    int src;
    int i, j, count, u, v, min;

    cout << "Enter source router (0 to " << N-1 << "): ";
    cin >> src;

    // Initialize dist[] and visited[]
    for (i = 0; i < N; i++) {
        dist[i] = cost[src][i];   // direct cost from source
        visited[i] = 0;           // not processed
    }
    dist[src] = 0;
    visited[src] = 1;

    // Dijkstra algorithm
    for (count = 1; count < N - 1; count++) {
        min = INF;
        u = -1;

        // find unvisited node with minimum distance
        for (i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        // relax edges from u
        for (v = 0; v < N; v++) {
            if (!visited[v] && cost[u][v] != INF
                && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "\nShortest distances from router " << src << ":\n";
    for (i = 0; i < N; i++) {
        cout << "To " << i << " = " << dist[i] << "\n";
    }

    return 0;
}
