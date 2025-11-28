#include <iostream>
using namespace std;

#define INF 9999
#define N 4   // number of routers

int main() {
    // Simple fixed graph
    int cost[N][N] = {
        {   0,   1,   4, INF },
        {   1,   0,   2,   6 },
        {   4,   2,   0,   3 },
        { INF,   6,   3,   0 }
    };

    int dist[N];
    int visited[N];
    int src = 0;           // fixed source router
    int i, j, count, u, v, min;

    // initialize
    for (i = 0; i < N; i++) {
        dist[i] = cost[src][i];   // direct cost from src
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;

    // Dijkstra
    for (count = 1; count < N - 1; count++) {
        min = INF;
        u = -1;

        // pick unvisited node with smallest dist
        for (i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        // relax neighbors
        for (v = 0; v < N; v++) {
            if (!visited[v] && cost[u][v] != INF &&
                dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "Shortest distances from router " << src << ":\n";
    for (i = 0; i < N; i++) {
        cout << "To " << i << " = " << dist[i] << "\n";
    }

    return 0;
}
